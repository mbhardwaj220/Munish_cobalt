// Copyright (c) 2014 Google Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/state_machine_shell.h"

#include "base/logging.h"

// --- Macros for common logging idioms ---

#define SM_STATE(s) GetStateString(s) << "(" << s << ")"
#define SM_STATEN(s) GetStateString(s) << "(" << s.value_or(0) << ")"
#define SM_EVENT(e) GetEventString(e) << "(" << e << ")"
#define SM_PREFIX \
    name_ << "-" << SM_STATEN(state_) << "v" << version_ << ": "
#define SM_DLOG(level) DLOG(level) << SM_PREFIX

namespace base {

StateMachineBaseShell::StateMachineBaseShell(const std::string &name)
    : name_(name),
      version_(0),
      is_handling_(false),
      is_initialized_(false),
      should_log_(false) {
}

void StateMachineBaseShell::Initialize() {
  if (is_initialized_) {
    return;
  }

  if (should_log_) {
    SM_DLOG(INFO) << "INITIALIZING";
  }
  DCHECK(!state_) << SM_PREFIX;
  DCHECK(!GetParentState(GetUserInitialState())) << SM_PREFIX;
  is_initialized_ = true;
  FollowInitialSubstates();
}

bool StateMachineBaseShell::IsIn(State state) const {
  StateN currentState = state_;
  while (currentState) {
    if (state == currentState.value()) {
      return true;
    }

    currentState = GetParentState(currentState);
  }

  return false;
}

const char *StateMachineBaseShell::GetStateString(StateN state) const {
  if (!state) {
    return "<none>";
  }

  const char *user = GetUserStateString(state.value());
  if (user) {
    return user;
  }

  return "UNKNOWN_STATE";
}

const char *StateMachineBaseShell::GetEventString(EventN event) const {
  if (!event) {
    return "<none>";
  }

  const char *user = GetUserEventString(event.value());
  if (user) {
    return user;
  }

  return "UNKNOWN_EVENT";
}

void StateMachineBaseShell::Handle(Event event, void *data) {
  Initialize();

  if (is_handling_) {
    if (should_log_) {
      SM_DLOG(INFO) << "QUEUEING " << SM_EVENT(event);
    }

    event_queue_.push(Bind(&StateMachineBaseShell::HandleOneEvent, Unretained(this),
                           event, Unretained(data)));
    return;
  }

  HandleOneEvent(event, data);
  HandleQueuedEvents();
}

StateMachineBaseShell::StateN
StateMachineBaseShell::GetParentState(StateN state) const {
  if (!state) {
    return StateN();
  }

  return GetUserParentState(state.value());
}

StateMachineBaseShell::StateN
StateMachineBaseShell::GetInitialSubstate(StateN state) const {
  if (!state) {
    return StateN();
  }

  return GetUserInitialSubstate(state.value());
}

void StateMachineBaseShell::HandleQueuedEvents() {
  while (!event_queue_.empty()) {
    event_queue_.front().Run();
    event_queue_.pop();
  }
}

void StateMachineBaseShell::HandleOneEvent(Event event, void *data) {
  if (should_log_) {
    SM_DLOG(INFO) << "HANDLING " << SM_EVENT(event);
  }

  DCHECK(!is_handling_) << SM_PREFIX;
  is_handling_ = true;

  // Walk up the hierarchy from the simplest current state, looking for event
  // handlers, stopping at the first state that decides to handle the event.
  StateN source = state_;
  Result result;
  while (source) {
    result = HandleUserStateEvent(source.value(), event, data);
    if (!result.is_handled) {
      // Result was not handled, so we continue up the state chain.
      source = GetParentState(source);
      continue;
    }

    break;
  }

  // Log that the event was completely unhandled, because that's kinda weird.
  // It's better if the state machine handler explicitly consumes and ignores
  // events that should be ignored.
  if (!result.is_handled && should_log_) {
    SM_DLOG(WARNING) << "Event " << SM_EVENT(event) << " was unhandled.";
  }

  // If a transition was triggered, execute it.
  if (result.is_transition) {
    Transition(event, source.value(), result.target.value(),
               result.is_external);
  }

  is_handling_ = false;
}

// Returns the index of |state| in |path|, or -1 if not found in |path_length|
// elements. If |state| is null, then it will always return -1.
static int IndexOf(StateMachineBaseShell::StateN state,
                   const StateMachineBaseShell::State *path,
                   size_t path_length) {
  if (!state) {
    return -1;
  }

  int i;
  for (i = 0; !(path[i] == state) && i < path_length; ++i) {
  }
  return (i == path_length ? -1 : i);
}

// Finds the least common ancestor between the two state paths. If there is no
// common ancestor, returns null.
static StateMachineBaseShell::StateN FindLeastCommonAncestor(
    const StateMachineBaseShell::State *path_a,
    size_t length_a,
    const StateMachineBaseShell::State *path_b,
    size_t length_b) {
  size_t max = std::min(length_a, length_b);
  size_t i;
  for (i = 0; path_a[i] == path_b[i] && i < max; ++i) { }
  return (i == 0 ? StateMachineBaseShell::StateN() : path_a[i - 1]);
}

void StateMachineBaseShell::GetPath(State state, size_t max_depth, State *out_path,
                                    size_t *out_depth) const {
  if (max_depth == 0) {
    SM_DLOG(FATAL) << "max_depth must be > 0";
    if (out_depth) {
      *out_depth = 0;
    }
    return;
  }

  size_t depth = 0;
  StateN currentState = state;
  while (currentState && depth < max_depth) {
    out_path[depth] = currentState.value();
    ++depth;
    currentState = GetParentState(currentState);
  }

  // Reverse so the path is in ascending depth order.
  std::reverse(out_path, out_path + depth);
  if (out_depth) {
    *out_depth = depth;
  }
}

void StateMachineBaseShell::Transition(Event event, State source, State target,
                                       bool is_external) {
  if (should_log_) {
    SM_DLOG(INFO) << SM_EVENT(event) << " caused " << SM_STATE(source) << " -> "
                  << SM_STATE(target) << (is_external ? " (external)" : "");
  }

  // Define a reasonable max depth so we don't have to heap allocate. I've never
  // seen an HSM as deep as whatever arbitrary value this is defined to be at
  // the moment.
  static const size_t kMaxDepth = 16;
  State source_path[kMaxDepth];
  size_t source_depth;
  GetPath(source, kMaxDepth, source_path, &source_depth);
  State target_path[kMaxDepth];
  size_t target_depth;
  GetPath(target, kMaxDepth, target_path, &target_depth);
  StateN least_common_ancestor =
      FindLeastCommonAncestor(source_path, source_depth, target_path,
                              target_depth);

  // External transitions must exit the source state and enter the target
  // state, so if the LCA is one of the two, we need to go one level up.
  if (is_external && (least_common_ancestor == source ||
                      least_common_ancestor == target)) {
    least_common_ancestor = GetParentState(least_common_ancestor);
  }

  // Unwind (exit) states up to the closest common ancestor.
  while (state_ && !(state_ == least_common_ancestor)) {
    ExitCurrentState();
  }

  // Update version before we wind down to the target.
  ++version_;

  // Wind (enter) states down to the target state.
  size_t next_depth = IndexOf(state_, target_path, target_depth) + 1;
  DCHECK_LE(next_depth, target_depth);
  while (next_depth < target_depth) {
    EnterState(target_path[next_depth]);
    ++next_depth;
  }

  FollowInitialSubstates();
}

void StateMachineBaseShell::FollowInitialSubstates() {
  while (true) {
    StateN substate =
        (state_ ? GetInitialSubstate(state_) : GetUserInitialState());
    if (!substate) {
      break;
    }
    EnterState(substate.value());
  }
}

void StateMachineBaseShell::EnterState(State state) {
  state_ = state;

  if (should_log_) {
    SM_DLOG(INFO) << "ENTER";
  }

  HandleUserStateEnter(state);
}

void StateMachineBaseShell::ExitCurrentState() {
  if (should_log_) {
    SM_DLOG(INFO) << "EXIT";
  }

  HandleUserStateExit(state_.value());
  state_ = GetParentState(state_);
}

}  // namespace base
