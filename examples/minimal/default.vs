#version 330

layout(location = 0) in vec3 vert_position;
layout(location = 1) in vec2 vert_texCoord;
layout(location = 2) in vec4 vert_color;

uniform mat4 uni_mvp;

out vec2 frag_texCoord;
out vec4 frag_color;

void main() {
  gl_Position = vec4(vert_position, 1.0) * uni_mvp;
  frag_texCoord = vert_texCoord;
  frag_color = vert_color;
}
