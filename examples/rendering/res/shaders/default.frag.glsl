#version 420

in vec2 frag_texCoord;

uniform vec4 uni_color;

out vec4 final;

uniform sampler2D sampler;

void main() {
  // float adjust = sin(frag_texCoord.x * 3.14) * sin(frag_texCoord.y * 3.14);

  // final = texture(sampler, frag_texCoord) * uni_color;
  // final = vec4(final.rgb, adjust);

  final = texture(sampler, frag_texCoord);
}
