/*
 * Copyright 2017 Google Inc. All Rights Reserved.
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

#ifndef COBALT_DOM_CAMERA_3D_H_
#define COBALT_DOM_CAMERA_3D_H_

#include "cobalt/input/camera_3d.h"
#include "cobalt/script/wrappable.h"

namespace cobalt {
namespace dom {

// 3D camera is used for setting the key mapping.
class Camera3D : public script::Wrappable {
 public:
  enum CameraAxes {
    // Restricted to [0deg, 360deg]
    kDomCameraRoll = input::Camera3D::kCameraRoll,
    // Restricted to [-90deg, 90deg]
    kDomCameraPitch = input::Camera3D::kCameraPitch,
    // Restricted to [0deg, 360deg]
    kDomCameraYaw = input::Camera3D::kCameraYaw,
  };

  explicit Camera3D(const scoped_refptr<input::Camera3D>& impl);

  // Creates a mapping between the specified keyCode and the specified camera
  // axis, such that while the key is pressed, the cameraAxis will rotate at a
  // constant rate of degrees_per_second.
  void CreateKeyMapping(int keycode, uint32 camera_axis,
                        float degrees_per_second);
  // Clears any key mapping associated with the specified keyCode, if they
  // exist.
  void ClearKeyMapping(int keycode);
  // Clears all key mappings created by previous calls to |CreateKeyMapping|.
  void ClearAllKeyMappings();

  // Resets the camera's orientation.
  void Reset();

  // Custom, not in any spec.
  scoped_refptr<input::Camera3D> impl() { return impl_; }

  DEFINE_WRAPPABLE_TYPE(Camera3D);

 private:
  // We delegate all calls to the implementation of Camera3D so that all camera
  // state is stored within an object that is *not* a script::Wrappable. This
  // is important because input::Camera3D will typically be attached to a render
  // tree, and render trees passed to the rasterizer have the potential to
  // outlive the WebModule that created them, and input::Camera3D is designed
  // for just this.
  scoped_refptr<input::Camera3D> impl_;

  DISALLOW_COPY_AND_ASSIGN(Camera3D);
};

}  // namespace dom
}  // namespace cobalt

#endif  // COBALT_DOM_CAMERA_3D_H_
