
add_executable("Minimal" WIN32 MACOSX_BUNDLE "Minimal.cpp")
target_link_libraries("Minimal" "canvas")
set_property(TARGET "Minimal" PROPERTY FOLDER "canvas/examples")
