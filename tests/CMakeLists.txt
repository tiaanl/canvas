
set(canvas_TEST_FILES
    "Math/Mat4Tests.cpp"
    "Math/TransformTests.cpp"
    "Math/Vec2Tests.cpp"
    "Math/Vec3Tests.cpp"
    "Math/Vec4Tests.cpp"
    "Rendering/FontTests.cpp"
)

add_executable(canvas_tests ${canvas_TEST_FILES})
target_link_libraries(canvas_tests googletest canvas nucleus)
set_property(TARGET canvas_tests PROPERTY FOLDER canvas)
