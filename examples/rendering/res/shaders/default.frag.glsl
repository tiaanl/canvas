#version 420

in vec2 frag_texCoord;

out vec4 final;

uniform sampler2D sampler;

void main() {
  final = vec4(1.0, 0.0, 0.0, 1.0);

  final = texture(sampler, frag_texCoord);
}
