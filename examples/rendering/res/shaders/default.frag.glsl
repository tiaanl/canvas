#version 420

in vec4 frag_color;
in vec2 frag_texCoords;
out vec4 final;
uniform sampler2D unif_texture;

void main() {
  final = texture(unif_texture, frag_texCoords);
  // final = frag_color;
}
