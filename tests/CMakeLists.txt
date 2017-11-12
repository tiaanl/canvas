
set(canvas_TEST_FILES
    "math/mat4_tests.cpp"
    "math/TransformTests.cpp"
    "math/vec2_tests.cpp"
    "math/vec3_tests.cpp"
    "math/vec4_tests.cpp"
    "rendering/font_tests.cpp"
)

add_executable(canvas_tests ${canvas_TEST_FILES})
target_link_libraries(canvas_tests googletest canvas nucleus)
set_property(TARGET canvas_tests PROPERTY FOLDER canvas)
