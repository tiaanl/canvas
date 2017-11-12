
project(libpng)

set(libpng_INCLUDE_FILES
	"png.h"
	"pngconf.h"
	"pngdebug.h"
	"pnginfo.h"
	"pnglibconf.h"
	"pngpriv.h"
	"pngstruct.h"
)

set(libpng_SOURCE_FILES
	"png.c"
	"pngerror.c"
	"pngget.c"
	"pngmem.c"
	"pngpread.c"
	"pngread.c"
	"pngrio.c"
	"pngrtran.c"
	"pngrutil.c"
	"pngset.c"
	"pngtrans.c"
	"pngwio.c"
	"pngwrite.c"
	"pngwtran.c"
	"pngwutil.c"
)

add_library(libpng ${libpng_INCLUDE_FILES} ${libpng_SOURCE_FILES})
target_link_libraries(libpng zlib)
target_include_directories(libpng PUBLIC "${libpng_SOURCE_DIR}")
set_property(TARGET "libpng" PROPERTY FOLDER "third_party")

if (WIN32)
	target_compile_definitions(libpng PRIVATE "-D_CRT_SECURE_NO_WARNINGS")
endif()
