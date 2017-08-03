// Copyright 2017 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

precision mediump float;

uniform vec4 u_color;
uniform vec4 u_texcoord_clamp;
uniform sampler2D u_texture;

// A rounded rect is represented by a vec4 specifying (min.xy, max.xy), and a
// matrix of corners. Each vector in the matrix represents a corner (order:
// top left, top right, bottom left, bottom right). Each corner vec4 represents
// (start.xy, radius.xy).
uniform vec4 u_rect;
uniform mat4 u_corners;

varying vec2 v_offset;
varying vec2 v_texcoord;

#include "function_is_outside_rrect.inc"

void main() {
  float scale = IsOutsideRRect(v_offset, u_rect, u_corners);
  gl_FragColor = u_color * (1.0 - scale) * texture2D(u_texture,
      clamp(v_texcoord, u_texcoord_clamp.xy, u_texcoord_clamp.zw));
}
