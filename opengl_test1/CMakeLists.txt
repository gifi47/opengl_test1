# CMakeList.txt: проект CMake для opengl_test1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (opengl_test1
	"opengl_test1.cpp" 
	"opengl_test1.h"
    "Rendering/Shader.h"
	"Rendering/Shader.cpp"
	"Utils/Utils.cpp"
	"Utils/Utils.h"
	"Rendering/Batch.h"
	"Rendering/Batch.cpp"
	"Rendering/Object.h" 
	"Rendering/Object.cpp" 
	"Rendering/Texture.h" 
	"Rendering/Texture.cpp"
	"TestObjects/Label.h"
	"TestObjects/Label.cpp"
	"Test/orbit.h"
	"Test/orbit.cpp"
	"Test/MultiTexObj.h"
	"Test/MultiTexObj.cpp"
	"Test/orbitInstanced.h"
	"Test/orbitInstanced.cpp"
	"Test/SimpleObj.h"
	"Test/SimpleObj.cpp")

target_link_libraries(opengl_test1
	${ALL_LIBS}
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET opengl_test1 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
