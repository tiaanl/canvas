
add_executable("ortho" WIN32 MACOSX_BUNDLE "ortho.cpp")
target_link_libraries("ortho" "canvas")
set_property(TARGET "ortho" PROPERTY FOLDER "canvas/examples")
