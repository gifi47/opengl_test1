#include "Shader.h"

Rendering::Shader::Shader(const std::string& name) {
    Initialize(name + ".vert", name + ".frag");
}

Rendering::Shader::Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath){
    Initialize(vertexShaderFilePath, fragmentShaderFilePath);
}

Rendering::Shader::Shader(const Shader& shader) {
	this->programId = shader.programId;
}

void Rendering::Shader::Use() {
    glUseProgram(this->programId);
}

void Rendering::Shader::Initialize(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
    const GLchar* vertexShaderSourceCode{ ReadFile(vertexShaderFilePath) };

    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vertexShaderSourceCode, nullptr);
    glCompileShader(vertexShaderId);

    CheckShaderErrors(vertexShaderId);

    const GLchar* fragmentShaderSourceCode{ ReadFile(fragmentShaderFilePath) };

    GLuint fragmentShaderId{ glCreateShader(GL_FRAGMENT_SHADER) };
    glShaderSource(fragmentShaderId, 1, &fragmentShaderSourceCode, nullptr);
    glCompileShader(fragmentShaderId);

    CheckShaderErrors(fragmentShaderId);

    this->programId = glCreateProgram();
    glAttachShader(this->programId, vertexShaderId);
    glAttachShader(this->programId, fragmentShaderId);
    glLinkProgram(this->programId);

    CheckProgramErrors(this->programId);

    glDetachShader(this->programId, vertexShaderId);
    glDetachShader(this->programId, fragmentShaderId);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    delete[] vertexShaderSourceCode;
    delete[] fragmentShaderSourceCode;
}

void Rendering::Shader::Dispose(){
    glDeleteProgram(this->programId);
}

void Rendering::Shader::CheckShaderErrors(const GLuint& shaderId) {
    GLint success;
    int infoLogLength;

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    glGetProgramiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (!success)
    {
        if (infoLogLength < 1) infoLogLength = 1000;
        std::vector<char> infoLog(infoLogLength + 1);
        glGetShaderInfoLog(shaderId, infoLogLength, nullptr, infoLog.data());
        std::cout << "Error: shader compilation error\n" << infoLog.data() << std::endl;
    }
}

void Rendering::Shader::CheckProgramErrors(const GLuint& programId) {
    GLint success;
    int infoLogLength;

    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (!success)
    {
        if (infoLogLength < 1) infoLogLength = 1000;
        std::vector<char> infoLog(infoLogLength + 1);
        glGetProgramInfoLog(programId, infoLogLength, nullptr, infoLog.data());
        std::cout << "Error: shader program compilation error\n" << infoLog.data() << std::endl;
    }
}
