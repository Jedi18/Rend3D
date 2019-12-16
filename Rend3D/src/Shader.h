#pragma once

#include "glad/glad.h"
#include<string>

class Shader
{
public:
	int program;
	Shader(const char* vertexShaderFilepath, const char* fragmentShaderFilepath);
	unsigned int CreateShader(const char* shaderSource, unsigned int type);
	unsigned int CreateProgram(unsigned int vertexShader, unsigned int fragmentShader);
	std::string ReadFileContents(const char* filepath);
	void Use() const;
	~Shader();
};