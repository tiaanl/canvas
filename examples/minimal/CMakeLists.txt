
add_executable("minimal" WIN32 MACOSX_BUNDLE "minimal.cpp")
target_link_libraries("minimal" "canvas")
set_property(TARGET "minimal" PROPERTY FOLDER "canvas/examples")
