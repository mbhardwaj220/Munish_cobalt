// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_CDM_INITIALIZED_PROMISE_H_
#define MEDIA_BASE_CDM_INITIALIZED_PROMISE_H_

#include <stdint.h>

#include "base/memory/ref_counted.h"
#include "media2/base/cdm_factory.h"
#include "media2/base/cdm_promise.h"
#include "media2/base/media_export.h"
#include "media2/base/media_keys.h"

namespace media {

// Promise to be resolved when the CDM is initialized. It owns the MediaKeys
// object until the initialization completes, which it then passes to
// |cdm_created_cb|.
class MEDIA_EXPORT CdmInitializedPromise : public SimpleCdmPromise {
 public:
  CdmInitializedPromise(const CdmCreatedCB& cdm_created_cb,
                        const scoped_refptr<MediaKeys>& cdm);
  ~CdmInitializedPromise() OVERRIDE;

  // SimpleCdmPromise implementation.
  void resolve() OVERRIDE;
  void reject(MediaKeys::Exception exception_code,
              uint32_t system_code,
              const std::string& error_message) OVERRIDE;

 private:
  CdmCreatedCB cdm_created_cb_;

  // Holds a ref-count of the CDM.
  scoped_refptr<MediaKeys> cdm_;
};

}  // namespace media

#endif  // MEDIA_BASE_CDM_INITIALIZED_PROMISE_H_
