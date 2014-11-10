/*
 * Copyright 2014 Google Inc. All Rights Reserved.
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

#ifndef RENDERER_BACKEND_GRAPHICS_CONTEXT_STUB_H_
#define RENDERER_BACKEND_GRAPHICS_CONTEXT_STUB_H_

#include "cobalt/renderer/backend/graphics_context.h"
#include "cobalt/renderer/backend/texture_stub.h"

namespace cobalt {
namespace renderer {
namespace backend {

// An implementation of GraphicsContext for the stub graphics system.
// Most methods are simply stubbed out and so this object does very little
// besides fight off compiler errors.
class GraphicsContextStub : public GraphicsContext {
 public:
  GraphicsContextStub() {}

  scoped_ptr<Texture> CreateTexture(
      int width, int height, SurfaceInfo::Format format, int pitch_in_pixels,
      scoped_array<uint8_t> data) OVERRIDE {
    return scoped_ptr<Texture>(
        new TextureStub(SurfaceInfo(width, height, format)));
  }

  void Clear(float red, float green, float blue, float alpha) OVERRIDE {}
  void BlitToRenderTarget(const Texture* texture) OVERRIDE {}

  void Submit() OVERRIDE {}
};

}  // namespace backend
}  // namespace renderer
}  // namespace cobalt

#endif  // RENDERER_BACKEND_GRAPHICS_CONTEXT_STUB_H_
