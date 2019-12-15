#include "Shader.h"

#include<fstream>
#include<sstream>
#include<iostream>

Shader::Shader(const char* vertexShaderFilepath, const char* fragmentShaderFilepath)
{
	unsigned int vertexShader = CreateShader(vertexShaderFilepath, GL_VERTEX_SHADER);
	unsigned int fragmentShader = CreateShader(fragmentShaderFilepath, GL_FRAGMENT_SHADER);
	
	program = CreateProgram(vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

unsigned int Shader::CreateShader(const char* shaderFilePath, unsigned int type)
{
	std::string source = ReadFileContents(shaderFilePath).c_str();
	const char* s = source.c_str();

	unsigned int shader = glCreateShader(type);

	glShaderSource(shader, 1, &s , NULL);
	glCompileShader(shader);

	// Error checking
	int success;
	char infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (success != GL_TRUE)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);

		std::cout << "ERROR::SHADER::COMPILATION::" << ((type == GL_VERTEX_SHADER) ? ("VERTEX_SHADER") : ("FRAGMENT_SHADER")) << std::endl;
		std::cout << infoLog << std::endl;

		return NULL;
	}

	return shader;
}

unsigned int Shader::CreateProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
	unsigned int program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	// check for errors during linking of shaders
	int success;
	char infoLog[512];

	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (success != GL_TRUE)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);

		std::cout << "ERROR::SHADER_PROGRAM::LINKING" << std::endl;
		std::cout << infoLog << std::endl;

		return 0;
	}

	return program;
}

std::string Shader::ReadFileContents(const char* filepath)
{
	std::ifstream filea;
	std::stringstream ss;
	std::string source;

	filea.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		filea.open(filepath, std::ios::in);
		ss << filea.rdbuf();
		source = ss.str();
		filea.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Error during reading of file " << filepath << "!" << std::endl;
		return NULL;
	}

	return source;
}

void Shader::Use() const
{
	glUseProgram(program);
}

Shader::~Shader()
{
	glDeleteProgram(program);
}