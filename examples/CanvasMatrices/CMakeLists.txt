set(SOURCE_FILES
    src/canvas_matrices.cpp
    )

nucleus_add_executable(CanvasMatrices WIN32 ${SOURCE_FILES})
target_link_libraries(CanvasMatrices PRIVATE canvas)
