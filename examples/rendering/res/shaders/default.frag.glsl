#version 420

// We get the texture coordinates from the vertex shader.
in vec2 frag_texCoord;
in vec4 frag_color;

// The bound texture.
uniform sampler2D sampler;

// The final color of the fragment.
out vec4 final;

void main() {
  final = texture(sampler, frag_texCoord);
}
