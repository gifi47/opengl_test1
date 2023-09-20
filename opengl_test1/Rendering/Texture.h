#pragma once

#include <GL/glew.h>
#include <string>
#include <SOIL/SOIL.h>

namespace Rendering {
	class Texture {
	public:
		Texture() = default;
		Texture(const std::string& filePath, int imageType);
		Texture(const Texture& texture);

		void Use();
		void Use(int id);
		void Initialize(const std::string& filePath, int imageType);
		void Dispose();
		
		GLuint textureId{};
	};
}