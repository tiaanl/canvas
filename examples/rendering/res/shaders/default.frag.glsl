#version 420

in vec2 frag_texCoord;

uniform vec4 uni_color;

out vec4 final;

uniform sampler2D sampler;

void main() {
  // final = texture(sampler, frag_texCoord);
  final = uni_color * 0.5 * texture(sampler, frag_texCoord);
}
