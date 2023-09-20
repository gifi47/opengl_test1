// opengl_test1.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <iostream>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <SOIL/SOIL.h>

#include "Rendering/Shader.h"
#include "Rendering/Batch.h"
#include "Rendering/Object.h"
#include "TestObjects/Label.h"
#include "Test/orbit.h"
#include "Test/MultiTexObj.h"
#include "Test/orbitInstanced.h"
#include "Test/SimpleObj.h"

// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.
