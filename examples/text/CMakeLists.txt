
add_executable(Text WIN32 MACOSX_BUNDLE "Text.cpp")
target_link_libraries(Text canvas)
set_property(TARGET Text PROPERTY FOLDER "canvas/examples")
