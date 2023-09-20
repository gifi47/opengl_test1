# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)

project ("opengl_test1")

find_package(OpenGL REQUIRED)

# Добавление внешнех зависимостей
add_subdirectory ("external")

include_directories(
	"external/glfw-3.3.8/include/"
	"external/glew-2.1.0/include/"
	"external/glm-0.9.9.8/"
	"external/soil-1.16/include/"
	"external/stb/"
	"external/assimp/include"
)

link_directories(
	"external/glew-2.1.0/lib/Release/x64/"
	"external/assimp/lib/x64/"
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	glew32s
	SOIL1_16
	assimp-vc143-mt
)

add_definitions(
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# Включите подпроекты.
add_subdirectory ("opengl_test1")
#add_subdirectory ("tut_code")
#add_subdirectory ("test_linux_project")
