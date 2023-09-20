# CMakeList.txt: проект CMake для opengl_test1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (tut_code
	"test_main.h"
	"test_main.cpp"
	"Test/Shader.h"
	"Test/Camera.h"
	"Test/Mesh.h"
	"Test/Model.h"
	"../opengl_test1/Rendering/Shader.h"
	"../opengl_test1/Rendering/Shader.cpp"
	"../opengl_test1/Rendering/Texture.h"
	"../opengl_test1/Rendering/Texture.cpp"
	"../opengl_test1/TestObjects/Label.h"
	"../opengl_test1/TestObjects/Label.cpp"
	"../opengl_test1/Utils/Utils.cpp"
	"../opengl_test1/Utils/Utils.cpp"
	)

target_link_libraries(tut_code
	${ALL_LIBS}
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET tut_code PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
