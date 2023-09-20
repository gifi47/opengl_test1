// opengl_test1.cpp: определяет точку входа для приложения.
//

#include "opengl_test1.h"

static int inputForward = 0;
static int inputSide = 0;
static int inputVertical = 0;
static int inputSideArrows = 0;

static bool stopRendering = 0;
static bool orbitRendering = 1;

#define media "C:\\Users\\User\\source\\repos\\OpenGL\\opengl_test1\\media\\"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	//forward
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		inputForward += 1;
	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		inputForward -= 1;
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		inputForward -= 1;
	if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		inputForward += 1;

	//side
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		inputSide -= 1;
	if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		inputSide += 1;
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		inputSide += 1;
	if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		inputSide -= 1;

	//vertical
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		inputVertical += 1;
	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
		inputVertical -= 1;
	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
		inputVertical -= 1;
	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE)
		inputVertical += 1;
	
	//side
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		inputSideArrows += 1;
	if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
		inputSideArrows -= 1;
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		inputSideArrows -= 1;
	if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
		inputSideArrows += 1;

	//stop rendering
	if (key == GLFW_KEY_T && action == GLFW_PRESS)
		stopRendering = !stopRendering;

	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		orbitRendering = !orbitRendering;
}

void batch(GLuint& VAO, GLuint& VBO, GLuint& EBO, std::vector<float>& verts, std::vector<int>& inds);

class Ahri {
public:
	Ahri(float x, float y, float z) {
		modelMatrix = {
			0.0015, 0, 0, 0,
			0, 0.0015, 0, 0,
			0, 0, 0.0015, 0,
			x, y, z, 1
		};
	}

	void Render(glm::mat4& projView) {
		glm::mat4 MVP = projView * modelMatrix;
		shader.Use();
		glUniformMatrix4fv(mvpUniformId, 1, GL_FALSE, &MVP[0][0]);
		texture.Use();
		model.Use();
	}

	glm::mat4 modelMatrix;

	static GLuint mvpUniformId;
	static Rendering::Batch model;
	static Rendering::Shader shader;
	static Rendering::Texture texture;
};

Rendering::Batch Ahri::model;
Rendering::Shader Ahri::shader;
Rendering::Texture Ahri::texture;
GLuint Ahri::mvpUniformId;

glm::mat4* BuildModelMatrixArray(unsigned int amount, float radius = 100.0f, float offset = 10.0f) {
	
	glm::mat4* modelMatrices = new glm::mat4[amount];

	for (unsigned int i = 0; i < amount; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		// 1. translation: displace along circle with 'radius' in range [-offset, offset]
		float angle = (float)i / (float)amount * 360.0f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float x = sin(angle) * radius + displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float y = displacement * 0.4f; // keep height of field smaller compared to width of x and z
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float z = cos(angle) * radius + displacement;
		model = glm::translate(model, glm::vec3(x, y, z));

		// 2. scale: scale between 0.05 and 0.25f
		float scale = (rand() % 20) / 100.0f + 0.05;
		model = glm::scale(model, glm::vec3(scale));

		// 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
		float rotAngle = (rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

		// 4. now add to list of matrices
		modelMatrices[i] = model;
	}
	return modelMatrices;
}

void startup() {
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		exit(-1);
	}
	//glfwWindowHint(GLFW_FSAA_SAMPLES, 4);
	//glfwWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	GLFWwindow* window = glfwCreateWindow(1920, 1080, "Ahri moment", NULL, NULL);
	if (!window) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		exit(-1);
	}

	glfwSetKeyCallback(window, key_callback);

	// Ensure we can capture the escape key being pressed below
	//glfwEnable(GLFW_STICKY_KEYS);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	std::vector<float> verts;
	std::vector<int> inds;

	ImportObj("C:\\Users\\User\\source\\repos\\laba5\\ahri.obj", verts);
	inds.resize(verts.size() / 8);
	for (int i = 0; i < inds.size(); i++) {
		inds[i] = i;
	}
	/*for (int i = 0; i < verts.size(); i += 3) {
		std::cout << verts[i] << " " << verts[i + 1] << " " << verts[i + 2] << "\n";
	}*/
	

	GLuint VAO, VBO, EBO;
	batch(VAO, VBO, EBO, verts, inds);
	Rendering::Shader shader("C:\\Users\\User\\source\\repos\\OpenGL\\opengl_test1\\media\\shaders\\mvp");
	
	glm::mat4 ahriModel = {
		0.01, 0, 0, 0,
		0, 0.01, 0, 0,
		0, 0, 0.01, 0,
		1, 0, 0, 1
	};

	std::string spiritBlossomhriFilePath = "C:\\Users\\User\\source\\repos\\OpenGL\\opengl_test1\\media\\models\\spiritBlossomAhri.obj";
	//std::string spiritBlossomhriFilePath = "C:\\Users\\User\\source\\repos\\OpenGL\\opengl_test1\\media\\models\\makaka.obj";

	//ImportObj("C:\\Users\\User\\source\\repos\\OpenGL\\opengl_test1\\media\\models\\ahri_xd3.obj", verts);
	ImportObj(spiritBlossomhriFilePath, verts);
	inds.resize(verts.size() / 8);
	for (int i = 0; i < inds.size(); i++) {
		inds[i] = i;
	}
	Rendering::Object ahri(verts, inds, "C:\\Users\\User\\source\\repos\\OpenGL\\opengl_test1\\media\\shaders\\mvp.vert", 
		"C:\\Users\\User\\source\\repos\\OpenGL\\opengl_test1\\media\\shaders\\mvp.frag", 
		"C:\\Users\\User\\source\\repos\\OpenGL\\opengl_test1\\media\\textures\\ahri_spirit_1.png", SOIL_LOAD_RGB, ahriModel);
	GLuint ahriMvpUniformId = glGetUniformLocation(ahri.shader.programId, "MVP");


	glm::mat4 model = {
		.61, 0, 0, 0,
		0, .61, 0, 0,
		0, 0, .61, 0,
		-1, 0, 0, 1
	};
	glm::mat4 view = glm::lookAt(
		glm::vec3(4, 3, 3),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);
	//glm::mat4 view = glm::lookAt(
	//	glm::vec3(0, 0, 0),
	//	glm::vec3(0, 0, 0),
	//	glm::vec3(0, 1, 0)
	//);
	glm::mat4 ortho_view = glm::lookAt(
		glm::vec3(0, 0, 3),
		glm::vec3(0, 0, 2),
		glm::vec3(0, 1, 0)
	);
	float zFar = 10000;
	glm::mat4 orth_proj = glm::ortho<float>(-1, 1, -1, 1, 0.1, zFar);
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, zFar);
	glm::mat4 MVP = proj * view * model;

	GLuint mvpUniformId = glGetUniformLocation(shader.programId, "MVP");
	//GLuint colorUniformId = glGetUniformLocation(shader.programId, "c");

	float speed = 0.00344f;
	// Camera position
	// 
	glm::vec3 cameraPos(0, 0, 100);
	//glm::vec3 cameraPos(0, 0, 3);
	//glm::vec3 cameraPos(0, 0, 1300);
	glm::vec3 cameraForward(0, 0, -1);
	glm::vec3 cameraUp(0, 1, 0);

	//rofl
	glm::vec3 color(1, 0, 0);

	int g = 0;
	//-------------

	//rotation
	float angleRot = 0.002;

	float cosA = glm::cos(angleRot);
	float sinA = glm::sin(angleRot);

	glm::mat3 rotRight = {
		cosA, 0, sinA,
		0, 1, 0,
		-sinA, 0, cosA,
	};

	cosA = glm::cos(-angleRot);
	sinA = glm::sin(-angleRot);

	glm::mat3 rotLeft = {
		cosA, 0, sinA,
		0, 1, 0,
		-sinA, 0, cosA,
	};

	// LABEL

	Rendering::Texture digit_tex("C:\\Users\\User\\source\\repos\\OpenGL\\opengl_test1\\media\\textures\\digits.png", SOIL_LOAD_RGBA);
	Rendering::Shader label_shader("C:\\Users\\User\\source\\repos\\OpenGL\\opengl_test1\\media\\shaders\\label.vert", "C:\\Users\\User\\source\\repos\\OpenGL\\opengl_test1\\media\\shaders\\label.frag");
	Test::Label label1(8, digit_tex, label_shader);
	glm::mat4 lebel1_m = {
		0.025, 0, 0, 0,
		0, 0.1, 0, 0,
		0, 0, 0.1, 0,
		-0.75, 0.75, 0, 1
	};
	glm::mat4 label1MVP = orth_proj * ortho_view * lebel1_m;
	//ExportObj("C:\\Users\\User\\source\\repos\\OpenGL\\opengl_test1\\media\\models\\out.obj", label1.verts, label1.tex, label1.indexes, true);


	double frameTimeStart = glfwGetTime();
	int frameCount = 0;

	proj = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, zFar);
	
	const int border = 1;
	std::vector<Ahri> vec_ahri;
	std::vector<float> vec_batch;
	std::vector<int> vec_inds;
	for (int _x = -border; _x < border; _x++) {
		for (int _y = -border; _y < border; _y++) {
			for (int _z = -border; _z < border; _z++) {
				vec_ahri.push_back(Ahri(_x, _y, _z));
				int offset = 0;
				for (int i = 0; i < verts.size(); i++) {
					if (offset < 3) {
						switch (offset % 3)
						{
						case 0:
							vec_batch.push_back((verts[i]) + _x);
							break;
						case 1:
							vec_batch.push_back((verts[i]) + _y);
							break;
						case 2:
							vec_batch.push_back((verts[i]) * _z);
							break;
						default:
							break;
						}
					}
					else vec_batch.push_back(verts[i]);
					offset++;
					if (offset > 7) {
						offset = 0;
					}
				}
			}
		}
	}
	vec_inds.resize(vec_batch.size() / 8);

	for (int i = 0; i < vec_inds.size(); i++) {
		vec_inds[i] = i;
	}
	Rendering::Batch batch_ahri(vec_batch, vec_inds);
	vec_batch.clear();
	vec_inds.clear();
	
	Ahri::model = ahri.batch;
	Ahri::shader = ahri.shader;
	Ahri::texture = ahri.texture;
	Ahri::mvpUniformId = glGetUniformLocation(ahri.shader.programId, "MVP");

	int orbitSize = 100;

	// большая Ари и вокруг неё орбита из Ари
	tst::Orbit orbit;
	orbit.Create(ahri.batch, ahri.batch, orbitSize);
	orbit.shader = ahri.shader;
	orbit.texture = ahri.texture;
	speed = 0.344f;

	//АРИ и несколько материалов
	Rendering::Shader multiMatShader("C:\\Users\\User\\source\\repos\\OpenGL\\opengl_test1\\media\\shaders\\multiTextureShader.vert", "C:\\Users\\User\\source\\repos\\OpenGL\\opengl_test1\\media\\shaders\\multiTextureShader.frag");
	tst::MultiTexObj ahriMT(spiritBlossomhriFilePath, multiMatShader);
	Rendering::Batch ahriMTBatch;

	orbit.rockShader = multiMatShader;
	ahriMTBatch.VAO = ahriMT.VAO;
	ahriMTBatch.EBO = ahriMT.EBO;
	ahriMTBatch.VBO = ahriMT.VBO;
	ahriMTBatch.vertexCount = ahriMT.vertexCount;

	orbit.uniformModifireLocation = glGetUniformLocation(multiMatShader.programId, "modifire");
	orbit.uniformMVPLocation = glGetUniformLocation(multiMatShader.programId, "MVP");

	orbit.rock = ahriMTBatch;

	// INSTANCED
	Rendering::Shader multiMatShaderInstanced("C:\\Users\\User\\source\\repos\\OpenGL\\opengl_test1\\media\\shaders\\multiTextureShaderInstanced.vert", "C:\\Users\\User\\source\\repos\\OpenGL\\opengl_test1\\media\\shaders\\multiTextureShaderInstanced.frag");
	tst::MultiTexObj ahriMTI(spiritBlossomhriFilePath, multiMatShaderInstanced);
	Rendering::Batch ahriMTIBatch;
	ahriMTIBatch.VAO = ahriMTI.VAO;
	ahriMTIBatch.EBO = ahriMTI.EBO;
	ahriMTIBatch.VBO = ahriMTI.VBO;
	ahriMTIBatch.vertexCount = ahriMTI.vertexCount;

	tst::OrbitInstanced orbitIntanced;
	orbitIntanced.Create(ahri.batch, ahriMTIBatch, orbitSize);
	orbitIntanced.shader = ahri.shader;
	orbitIntanced.texture = ahri.texture;
	orbitIntanced.rockShader = multiMatShaderInstanced;

	// Новая улучшенная версия
	// 
	Rendering::Shader sObjShader(media "shaders\\tut\\rock.vert", media "shaders\\tut\\rock.frag");
	Rendering::Shader sObjShaderMVP(media "shaders\\tut\\rockMVP.vert", media "shaders\\tut\\rock.frag");
	Rendering::Texture sObjTexture(media "textures\\asteroid.png", SOIL_LOAD_RGB);
	Rendering::Texture sObjPlanetTexture(media "textures\\jupiter.png", SOIL_LOAD_RGB);
	tst::SimpleObj sObj(media "models\\rockobj.obj", sObjShader, sObjTexture);
	tst::SimpleObj sObjPlanet(media "models\\planet.obj", sObjShaderMVP, sObjPlanetTexture);
	//tst::SimpleObj sObj(media "models\\spiritBlossomAhri.obj", sObjShader, ahri.texture);

	glm::mat4* modelMatrices = BuildModelMatrixArray(orbitSize, 50, 2.5f);
	sObj.BindInstantModelMatricesBuffer(orbitSize, modelMatrices);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cameraPos.x += speed * inputSide * (- cameraForward.z) + speed * inputForward * cameraForward.x;
		cameraPos.z += speed * inputForward * cameraForward.z + speed * inputSide * cameraForward.x;
		cameraPos.y += speed * inputVertical;

		if (inputSideArrows == 1) {
			cameraForward = rotRight * cameraForward;
		}
		else if (inputSideArrows == -1) {
			cameraForward = rotLeft * cameraForward;
		}

		if (!stopRendering) {
			view = glm::lookAt(
				cameraPos,
				cameraPos + cameraForward,
				cameraUp
			);
			//proj = glm::perspective(glm::radians(45.0f), 1.777777777777778f, 0.1f, 100.0f);
/*			MVP = proj * view * model;

			shader.Use();
			glUniformMatrix4fv(mvpUniformId, 1, GL_FALSE, &MVP[0][0]);
			//glUniform3fv(colorUniformId, 1, &color[0]);
			glBindTexture(GL_TEXTURE_2D, textureId);
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, inds.size(), GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);

			MVP = proj * view * ahri.modelMatrix;
			ahri.shader.Use();
			glUniformMatrix4fv(ahriMvpUniformId, 1, GL_FALSE, &MVP[0][0]);
			ahri.texture.Use();
			ahri.batch.Use();
*/
			glm::mat4 projView = proj * view;
			/*Ahri::shader.Use();
			glUniformMatrix4fv(Ahri::mvpUniformId, 1, GL_FALSE, &MVP[0][0]);
			Ahri::texture.Use();
			batch_ahri.Use();*/
			

			//for (int i = 0; i < vec_ahri.size(); i++) vec_ahri[i].Render(projView);
			/*if (orbitRendering)
				orbit.Draw(projView);
			else 
				orbitIntanced.Draw(projView);

			*/
			sObj.Instantiate(proj, view);
			sObjPlanet.Render(projView);
			//sObj.Instantiate(proj, view);
			//ahriMT.Render(projView);
		}

		
		//FPS COUNTER LABEL
		label1.Render(&label1MVP[0][0]);

		glfwSwapBuffers(window);

		double frameTimeEnd = glfwGetTime();
		frameCount++;
		if (frameTimeEnd - frameTimeStart >= 1.0) {
			label1.SetValue(frameCount);
			frameCount = 0;
			frameTimeStart = frameTimeEnd;
		}
	}
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	digit_tex.Dispose();
	label_shader.Dispose();
	label1.Dispose();

	//batch_ahri.Dispose();

	orbitIntanced.Dispose();
	ahri.Dispose();
	shader.Dispose();
	//ahriMT.Dispose();
	//multiMatShader.Dispose();
	ahriMTI.Dispose();
	multiMatShaderInstanced.Dispose();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void batch(GLuint& VAO, GLuint& VBO, GLuint& EBO, std::vector<float>& verts, std::vector<int>& inds) {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verts.size(), verts.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * inds.size(), inds.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)nullptr);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (GLvoid*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	/*glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texture_coord));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texture_id));
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(4);*/

	glBindVertexArray(0);
}

int main()
{
	srand(2441);
	startup();
	return 0;
}
