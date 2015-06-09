
add_executable("text" WIN32 MACOSX_BUNDLE "text.cpp")
target_link_libraries("text" "canvas")
set_property(TARGET "text" PROPERTY FOLDER "canvas/examples")
