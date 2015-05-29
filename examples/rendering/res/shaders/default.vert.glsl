#version 420

layout(location = 0) in vec2 vert_position;
layout(location = 1) in vec2 vert_texCoord;

uniform mat4 uni_mvp;

out vec2 frag_texCoord;

void main() {
  gl_Position = vec4(vert_position, 0.0, 1.0) * uni_mvp;
  frag_texCoord = vert_texCoord;
}