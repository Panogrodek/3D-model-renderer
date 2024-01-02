#include "pch.h"
#include "Rendering/Shader.hpp"
#include <GLEW/glew.h>
#include <fstream>



#include <glm/gtc/type_ptr.hpp>
static GLenum ShaderTypeFromString(const std::string& type) {
	if (type == "vertex") return GL_VERTEX_SHADER;
	if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;

	ASSERT(true); //"Unknown shader type!"
	return 0;
}

Shader::Shader(const std::string& filepath)
{
	std::string source = ReadFile(filepath);
	auto shaderSources = PreProcess(source);
	Compile(shaderSources);

	// Extract name from filepath
	auto lastSlash = filepath.find_last_of("/\\");
	lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
	auto lastDot = filepath.rfind('.');
	auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
	filepath.substr(lastSlash, count);
}

Shader::Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	: m_Name(name)
{
	std::unordered_map<GLenum, std::string> sources;
	sources[GL_VERTEX_SHADER] = vertexSrc;
	sources[GL_FRAGMENT_SHADER] = fragmentSrc;

	Compile(sources);
}
Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

std::string Shader::ReadFile(const std::string& filepath) {
	std::string result;
	std::ifstream in(filepath, std::ios::in | std::ios::binary);
	if (in)
	{
		in.seekg(0, std::ios::end); //gets the file char length
		result.resize(in.tellg());
		in.seekg(0, std::ios::beg); //sets the flag to the beginning 
		in.read(&result[0], result.size()); //loads the file into a string
		in.close();
	}
	else
	{
		std::cout << "Could not open file:" <<  filepath << "\n";
	}

	return result;
}

std::unordered_map<GLenum, std::string> Shader::PreProcess(const std::string& source)
{
	std::unordered_map<GLenum, std::string> shaderSources;

	const char* typeToken = "#type";
	size_t typeTokenLength = strlen(typeToken);
	size_t pos = source.find(typeToken, 0);
	while (pos != std::string::npos) {
		size_t eol = source.find_first_of("\r\n", pos);
		ASSERT(eol == std::string::npos); //Syntax error
		size_t begin = pos + typeTokenLength + 1;
		std::string type = source.substr(begin, eol - begin);
		ASSERT(!ShaderTypeFromString(type)); //Invalid shader type specification!

		size_t nextLinePos = source.find_first_not_of("\r\n", eol);
		pos = source.find(typeToken, nextLinePos);
		shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos,
			pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));

	}

	return shaderSources;
}

void Shader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
{
	GLuint program = glCreateProgram();
	ASSERT(shaderSources.size() > 2); //There can only be 2 shaders
	std::array<GLenum, 2> glShaderIDs{};
	int glShaderIDIndex = 0;
	for (auto& kv : shaderSources) {
		GLenum shaderType = kv.first;
		const std::string& source = kv.second;

		GLuint shader = glCreateShader(shaderType);

		const GLchar* sourceCStr = (const GLchar*)source.c_str();
		glShaderSource(shader, 1, &sourceCStr, 0);

		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(shader);

			ASSERT(true); //Shader failed to compile
			break;
		}
		glAttachShader(program, shader);
		glShaderIDs[glShaderIDIndex++] = (shader);
	}

	m_RendererID = program;

	glLinkProgram(program);

	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		glDeleteProgram(program);

		for (auto id : glShaderIDs)
			glDeleteShader(id);

		ASSERT(true); //failed to link shader
		return;
	}

	for (auto id : glShaderIDs)
		glDetachShader(program, id);
}


void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}
void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetInt(const std::string& name, const int value)
{
	UploadUniformInt(name, value);
}

void Shader::SetIntArray(const std::string& name, int* values, uint32_t count)
{
	UploadUniformIntArray(name, values, count);
}

void Shader::SetFloat(const std::string& name, const float value)
{
	UploadUniformFloat(name, value);
}

void Shader::SetFloat3(const std::string& name, const glm::vec3& value)
{
	UploadUniformFloat3(name, value);
}

void Shader::SetFloat4(const std::string& name, const glm::vec4& value)
{
	UploadUniformFloat4(name, value);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& value)
{
	UploadUniformMat4(name, value);
}

void Shader::UploadUniformInt(const std::string& name, const int value)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform1i(location, value);
}
void Shader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform1iv(location, count, values);
}
void Shader::UploadUniformFloat(const std::string& name, const float value)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform1f(location, value);
}
void Shader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform2f(location, value.x, value.y);
}
void Shader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform3f(location, value.x, value.y, value.z);
}
void Shader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform4f(location, values.x, values.y, values.z, values.w);
}
void Shader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}