#include "pch.h"
#include "Rendering/ModelLoader.hpp"

#include <fstream>

using namespace priv;

inline std::string ErasePart(char symbol, std::string& line)
{
	if (line.find(symbol) == std::string::npos)
		return "";

	int index = line.find(symbol) + 1;
	std::string part = line.substr(0, index);
	line.erase(0, index);

	return part;
}

void ModelLoader::Load(std::string path, std::string modelName)
{
	if (m_models.find(modelName) != m_models.end())
		std::cout << "overriding model data at " << modelName << "!\n";

	m_models[modelName] = Model();
	m_models[modelName].name = modelName;
	
	//Loading model from obj file
	static std::fstream file;
	file.open(path, std::ios::in | std::ios::binary);
	std::string line;

	while (std::getline(file, line)) {
		if (line.length() == 0)
			continue;
		Process(line, m_models[modelName]);
	}
	file.close();
}

Model& ModelLoader::GetModel(std::string name)
{
	ASSERT(m_models.find(name) == m_models.end()); //Accesing model that isn't loaded!
	return m_models[name];
}

void ModelLoader::Process(std::string line, Model& model)
{
	std::string symbol = ErasePart(' ',line);
	Vertex v;
	switch (symbol[0])
	{
	case '#':
		return;
	case 'v':
		v.position = glm::vec3{std::stof(ErasePart(' ',line)),std::stof(ErasePart(' ',line)),std::stof(line)};
		model.mesh.vertices.push_back(v);
		break;
	case 'vn': //TODO: this propably does not work like this
		model.mesh.vertices.back().normal = 
			glm::vec3{std::stof(ErasePart(' ',line)),std::stof(ErasePart(' ',line)),std::stof(line)};
		break;
	case 'vt': //TODO: same here
		model.mesh.vertices.back().texCoords =
			glm::vec2{ std::stof(ErasePart(' ',line)),std::stof(line) };
		break;
	case 'f':
		model.mesh.indices.push_back(std::stoi(ErasePart(' ', line)) - 1);
		model.mesh.indices.push_back(std::stoi(ErasePart(' ', line)) - 1);
		model.mesh.indices.push_back(std::stoi(line) - 1);
		break;
	default:
		break;
	}
}
