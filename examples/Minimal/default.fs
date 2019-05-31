#version 330

in vec2 uTextureCoord;

uniform sampler2D uTexture;

out vec4 final;

void main() {
  final = texture(uTexture, uTextureCoord);
}
