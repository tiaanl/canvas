#version 420

layout(location = 0) in vec2 vert_position;
layout(location = 1) in vec2 vert_texCoord;

out vec2 frag_texCoord;

void main() {
  gl_Position = vec4(vert_position, 0.0, 1.0);
  frag_texCoord = vert_texCoord;
}
