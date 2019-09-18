
set(canvas_TEST_FILES
    "Math/Mat4Tests.cpp"
    "Math/TransformTests.cpp"
    "Math/Vec2Tests.cpp"
    "Math/Vec3Tests.cpp"
    "Math/Vec4Tests.cpp"
    "Renderer/UniformBufferTests.cpp"
    "Renderer/VertexDefinitionTests.cpp"
)

add_executable(canvasTests ${canvas_TEST_FILES})
target_link_libraries(canvasTests canvas testing)
set_property(TARGET canvasTests PROPERTY FOLDER canvas)
