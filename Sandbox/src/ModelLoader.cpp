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
	static BufferLayout layout;
	if (layout.GetElements().empty()) {
		layout = BufferLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float3, "a_Normal" },
			{ ShaderDataType::Float2, "a_TexCoords" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float,  "a_TexIndex" },
		});
	}


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
	vertexNormalsIndex = 0;
	file.close();

	auto& model = m_models[modelName];
	model.vb = new VertexBuffer(model.mesh.vertices.size() * sizeof(Vertex));
	model.ib = new IndexBuffer(model.mesh.indices.data(), model.mesh.indices.size() * sizeof(uint32_t));
	model.va = new VertexArray();
	model.vb->SetLayout(layout);
	model.vb->SetData(model.mesh.vertices.data(), model.mesh.vertices.size() * sizeof(Vertex));
	model.va->SetIndexBuffer(model.ib);
	model.va->AddVertexBuffer(model.vb);
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
		model.mesh.vertices[vertexNormalsIndex].normal =
			glm::vec3{std::stof(ErasePart(' ',line)),std::stof(ErasePart(' ',line)),std::stof(line)};
		vertexNormalsIndex++;
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
