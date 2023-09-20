#pragma once

#include <gl/glew.h>
#include <string>
#include <iostream>
#include <vector>
#include "../Utils/Utils.h"

namespace Rendering {
	class Shader {
	public:
		Shader() = default;
		Shader(const std::string& name);
		Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		Shader(const Shader& shader);

		void Use();
		void Initialize(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void Dispose();

		GLuint programId{};

		static void CheckShaderErrors(const GLuint& shaderId);
		static void CheckProgramErrors(const GLuint& programId);
	};

}