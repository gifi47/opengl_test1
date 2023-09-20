#include "MultiTexObj.h"

tst::MultiTexObj::MultiTexObj(std::string modelFileName, Rendering::Shader shader) {
	std::vector<float> vertices;
	std::map<std::string, int> materials = ImportObjMultiTex(modelFileName, vertices);

	this->shader = shader;
	texture3 = Rendering::Texture("C:\\Users\\User\\source\\repos\\OpenGL\\opengl_test1\\media\\textures\\ahri_spirit_1.png", SOIL_LOAD_RGB);
	for (auto it = materials.begin(); it != materials.end(); it++) {
		std::string materialName = (*it).first;
		switch ((*it).second)
		{
		case 0:
			texture0 = Rendering::Texture("C:\\Users\\User\\source\\repos\\OpenGL\\opengl_test1\\media\\textures\\ahri_spirit_1.png", SOIL_LOAD_RGB);
			break;
		case 2:
			texture2 = Rendering::Texture("C:\\Users\\User\\source\\repos\\OpenGL\\opengl_test1\\media\\textures\\tail.png", SOIL_LOAD_RGB);
			break;
		case 1:
			texture1 = Rendering::Texture("C:\\Users\\User\\source\\repos\\OpenGL\\opengl_test1\\media\\textures\\tails.png", SOIL_LOAD_RGB);
			break;
		case 3:
			texture3 = Rendering::Texture(materialName, SOIL_LOAD_RGB);
			break;
		default:
			break;
		}
	}

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	std::vector<int> indexes(vertices.size() / 9);
	for (int i = 0; i < indexes.size(); i++) {
		indexes[i] = i;
	}

	this->vertexCount = indexes.size();

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indexes.size(), indexes.data(), GL_STATIC_DRAW);

	// XYZ ����������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid*)nullptr);
	glEnableVertexAttribArray(0);

	// RGB ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// ���������� ����������
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// ID ��������
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// ��������� �������
	modelMatrix = glm::mat4(1);

	// ���������� ������� �������
	/*glUniform1i(glGetUniformLocation(shader.programId, "tex0"), 0);
	glUniform1i(glGetUniformLocation(shader.programId, "tex1"), 1);
	glUniform1i(glGetUniformLocation(shader.programId, "tex2"), 2);
	glUniform1i(glGetUniformLocation(shader.programId, "tex3"), 3);*/
}

void tst::MultiTexObj::Render(const glm::mat4& projView)
{
	glm::mat4 MVP = projView * modelMatrix;
	this->shader.Use();
	glUniformMatrix4fv(glGetUniformLocation(this->shader.programId, "MVP"), 1, GL_FALSE, &MVP[0][0]);
	this->texture0.Use(0);
	this->texture1.Use(1);
	this->texture2.Use(2);
	this->texture3.Use(3);
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

void tst::MultiTexObj::Dispose()
{
	texture0.Dispose();
	texture1.Dispose();
	texture2.Dispose();
	glDeleteBuffers(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
}
