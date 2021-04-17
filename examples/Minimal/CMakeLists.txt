project(Minimal)

nucleus_add_executable(Minimal WIN32 MACOSX_BUNDLE Minimal.cpp)
target_link_libraries(Minimal canvas)

function(copy_dependency file)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/${file}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endfunction(copy_dependency)

copy_dependency(default.fs)
copy_dependency(default.png)
copy_dependency(default.vs)
