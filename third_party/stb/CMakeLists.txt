add_library(stb include/stb/stb_image.h)
set_target_properties(stb PROPERTIES LINKER_LANGUAGE C)
target_compile_definitions(stb PUBLIC -DSTB_IMAGE_IMPLEMENTATION)
