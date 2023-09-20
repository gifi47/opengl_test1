#include "Texture.h"

Rendering::Texture::Texture(const std::string& filePath, int imageType){
	Initialize(filePath, imageType);
}

Rendering::Texture::Texture(const Texture& texture){
	this->textureId = texture.textureId;
}

void Rendering::Texture::Use(){
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textureId);
}

void Rendering::Texture::Use(int id) {
	glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(GL_TEXTURE_2D, this->textureId);
}

void Rendering::Texture::Initialize(const std::string& filePath, int imageType){
	int textureWidth, textureHeight;
	unsigned char* texture = SOIL_load_image(filePath.c_str(), &textureWidth, &textureHeight, 0, imageType);
	glGenTextures(1, &this->textureId);

	glBindTexture(GL_TEXTURE_2D, this->textureId);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, (imageType == SOIL_LOAD_RGB ? GL_RGB : GL_RGBA), textureWidth, textureHeight, 0, (imageType == SOIL_LOAD_RGB ? GL_RGB : GL_RGBA), GL_UNSIGNED_BYTE, texture);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(texture);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Rendering::Texture::Dispose(){
	glDeleteTextures(1, &this->textureId);
}
