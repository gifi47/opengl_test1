# CMakeList.txt: 
# 
#

### GLFW ###

add_subdirectory ("glfw-3.3.8")

include_directories(
	"glfw-3.3.8/include/GLFW/"
	"glew-2.1.0/include/"
	"soil-1.16/include/"
	"stb/"
	"assimp/include/"
)

### SOIL ###

#add_subdirectory("soil-1.16")

set(SOIL_SOURCE
	"soil-1.16/src/soil.c"
	"soil-1.16/src/stb_image_aug.c"
	"soil-1.16/src/image_helper.c"
	"soil-1.16/src/image_dxt.c"
	#"soil-1.16/src/original/stb_image-1.09.c"
	#"soil-1.16/src/original/stb_image-1.16.c"
)

set(SOIL_HEADERS
	"soil-1.16/include/SOIL/SOIL.h"
	"soil-1.16/include/SOIL/stb_image_aug.h"
	"soil-1.16/include/SOIL/image_helper.h"
	"soil-1.16/include/SOIL/image_dxt.h"
	"soil-1.16/include/SOIL/stbi_dds_aug.h"
	"soil-1.16/include/SOIL/stbi_dds_aug_c.h"
)

add_library(
	SOIL1_16 
	STATIC
	${SOIL_SOURCE}
	${SOIL_HEADERS}
)