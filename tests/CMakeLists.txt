
set(canvas_TEST_FILES
    "Math/Mat4Tests.cpp"
    "Math/TransformTests.cpp"
    "Math/Vec2Tests.cpp"
    "Math/Vec3Tests.cpp"
    "Math/Vec4Tests.cpp"
    "Rendering/FontTests.cpp"
    "Resources/ResourceManagerTests.cpp"
    "Resources/ResourceTests.cpp"
)

add_executable(canvasTests ${canvas_TEST_FILES})
target_link_libraries(canvasTests testing canvas nucleus)
set_property(TARGET canvasTests PROPERTY FOLDER canvas)
