/*
 * Copyright 2015 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef COBALT_H5VCC_H5VCC_SYSTEM_H_
#define COBALT_H5VCC_H5VCC_SYSTEM_H_

#include <string>

#include "cobalt/script/wrappable.h"

namespace cobalt {
namespace h5vcc {

class H5vccSystem : public script::Wrappable {
 public:
  explicit H5vccSystem(const base::Callback<void(bool)>& on_set_record_stats);

  bool are_keys_reversed() const;
  std::string build_id() const;
  std::string platform() const;
  std::string region() const;
  std::string version() const;
  bool record_stats() const {
    return record_stats_;
  }
  void set_record_stats(bool record_stats) {
    record_stats_ = record_stats;

    on_set_record_stats_.Run(record_stats);
  }

  bool TriggerHelp() const;
  std::string GetVideoContainerSizeOverride() const;

  DEFINE_WRAPPABLE_TYPE(H5vccSystem);

 private:
  base::Callback<void(bool)> on_set_record_stats_;
  bool record_stats_;
  DISALLOW_COPY_AND_ASSIGN(H5vccSystem);
};

}  // namespace h5vcc
}  // namespace cobalt

#endif  // COBALT_H5VCC_H5VCC_SYSTEM_H_
