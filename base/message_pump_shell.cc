#include "message_pump_shell.h"
#include "base/logging.h"

namespace base {

MessagePumpShell::MessagePumpShell()
  : keep_running_(true),
    event_(false, false) {
}

bool MessagePumpShell::DoWork() {
  NOTREACHED();
  return false;
}

bool MessagePumpShell::DoDelayedWork(TimeTicks *next_delayed_work_time) {
  NOTREACHED();
  return false;
}

bool MessagePumpShell::DoIdleWork() {
  NOTREACHED();
  return false;
}

void MessagePumpShell::Run(Delegate * delegate) {
  DCHECK(keep_running_) << "Quit must have been called outside of Run!";

  for (;;) {
    bool did_work = delegate->DoWork();
    if (!keep_running_)
      break;

    bool did_delayed_work = false;
    // Let's play catchup on all delayed work before we loop.
    // This fixes bug #5534709 by processing a large number of
    // short delayed tasks (like WebKitClientImpl's stuff)
    // quickly before looping back to process non-delayed tasks
    // (like paint).  Otherwise, WebKitClientImpl's stuff
    // (including everything in WebCore & JSC) gets starved out
    // because the backlog of delayed tasks only gets processed
    // at one task per drawn frame.
    do {
      did_delayed_work = delegate->DoDelayedWork(&delayed_work_time_);
      did_work |= did_delayed_work;
    } while (did_delayed_work && keep_running_);

    if (!keep_running_)
      break;

    if (did_work)
      continue;

    did_work = delegate->DoIdleWork();
    if (!keep_running_)
      break;

    if (did_work)
      continue;

    if (delayed_work_time_.is_null()) {
      event_.Wait();
    } else {
      TimeDelta delay = delayed_work_time_ - TimeTicks::Now();
      if (delay > TimeDelta()) {
        event_.TimedWait(delay);
      } else {
        // It looks like delayed_work_time_ indicates a time in the past, so we
        // need to call DoDelayedWork now.
        delayed_work_time_ = TimeTicks();
      }
    }
    // Since event_ is auto-reset, we don't need to do anything special here
    // other than service each delegate method.
  }
  keep_running_ = true;
}

void MessagePumpShell::Quit() {
  keep_running_ = false;
}

void MessagePumpShell::ScheduleWork() {
  event_.Signal();
}

void MessagePumpShell::ScheduleDelayedWork(const TimeTicks& delayed_work_time) {
  delayed_work_time_ = delayed_work_time;
}

void MessagePumpShell::RunWithDispatcher(Delegate* delegate, Dispatcher* dispatcher) {
  NOTREACHED();
}

void MessagePumpShell::AddObserver(Observer* observer) {
  NOTREACHED();
}

void MessagePumpShell::RemoveObserver(Observer* observer) {
  NOTREACHED();
}

bool MessagePumpShell::WatchSocket(int s,
                                   bool persistent,
                                   Mode mode,
                                   FileDescriptorWatcher *controller,
                                   Watcher *del) {
  NOTREACHED();
  return false;
}

} // namespace base
