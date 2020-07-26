# canvas
[canvas](https://github.com/tiaanl/canvas) is a general purpose rendering library based on [OpenGL](https://www.opengl.org).  It uses [glfw](https://github.com/glfw/glfw) for windowing and [glad](https://github.com/Dav1dde/glad) as an OpenGL loader.

## Example usage

A simple example is pseudo code:

```c++
Renderer renderer;

VertexDefinition def;
def.addAttribute(ComponentType::Float32, ca::ComponentCount::Three);
auto vertexBuffer = renderer.createVertexBuffer(def, vertices, 6);

auto program = renderer.createProgram(ShaderSource{vs}, ShaderSource{fs});

renderer.draw(DrawType::Triangles), 6, program, vertexBuffer);
```

See [examples/Minimal/Minimap.cpp]() for more detailed example.
