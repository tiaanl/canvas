
set(canvas_TEST_FILES
    "Math/Mat4Tests.cpp"
    "Math/Vec2Tests.cpp"
    "Math/Vec3Tests.cpp"
    "Math/Vec4Tests.cpp"
    "Renderer/EncoderTests.cpp"
    "Renderer/VertexDefinitionTests.cpp"
    "Rendering/FontTests.cpp"
)

add_executable(canvasTests ${canvas_TEST_FILES})
target_link_libraries(canvasTests canvas nucleus testing)
set_property(TARGET canvasTests PROPERTY FOLDER canvas)
