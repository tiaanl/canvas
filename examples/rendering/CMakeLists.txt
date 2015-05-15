
add_executable("rendering" WIN32 MACOSX_BUNDLE "rendering.cpp")
target_link_libraries("rendering" "canvas")
set_property(TARGET "rendering" PROPERTY FOLDER "canvas/examples")
