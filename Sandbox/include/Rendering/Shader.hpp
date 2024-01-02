#pragma once

#include <GLM/glm.hpp>

typedef unsigned int GLenum;

class Shader {
public:
	Shader(const std::string& filepath);
	Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	~Shader();

	void Bind() const;
	void Unbind() const;

	virtual void SetInt(const std::string& name, const int value);
	virtual void SetIntArray(const std::string& name, int* values, uint32_t count);
	virtual void SetFloat(const std::string& name, const float value);
	virtual void SetFloat3(const std::string& name, const glm::vec3& value);
	virtual void SetFloat4(const std::string& name, const glm::vec4& value);
	virtual void SetMat4(const std::string& name, const glm::mat4& value);

	virtual const std::string& GetName() const { return m_Name; };

	void UploadUniformInt(const std::string& name, const int value);
	void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);

	void UploadUniformFloat(const std::string& name, const float value);
	void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
	void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
	void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

	void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
	void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
private:
	std::string ReadFile(const std::string& filepath);
	std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
	void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
private:
	uint32_t m_RendererID;
	std::string m_Name;
};