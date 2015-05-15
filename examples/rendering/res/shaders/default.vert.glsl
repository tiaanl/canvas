#version 420

layout(location = 0) in vec2 vert_position;
layout(location = 1) in vec3 vert_color;
layout(location = 2) in vec2 vert_texCoords;

out vec4 frag_color;
out vec2 frag_texCoords;

void main() {
  // Set the position.
  gl_Position = vec4(vert_position, 0.0, 1.0);
  
  // Forward the color and the texture coordinates.
  frag_color = vec4(vert_color, 1.0);
  frag_texCoords = vert_texCoords;
}
