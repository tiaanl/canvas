#version 330

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTextureCoord;

uniform float uScale;

out vec2 uTextureCoord;

void main() {
  gl_Position = vec4(inPosition * uScale, 1.0);
  uTextureCoord = inTextureCoord;
}
