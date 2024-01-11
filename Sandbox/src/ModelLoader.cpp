#include "pch.h"
#include "Rendering/ModelLoader.hpp"

#include <fstream>

using namespace priv;

std::string ErasePart(char symbol, std::string& line)
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
	layout = BufferLayout({
		{ ShaderDataType::Float3, "a_Position" },
		{ ShaderDataType::Float3, "a_Normal" },
		{ ShaderDataType::Float2, "a_TexCoords" },
		{ ShaderDataType::Float4, "a_Color" },
		{ ShaderDataType::Float,  "a_TexIndex" },
	});


	if (m_models.find(modelName) != m_models.end())
		std::cout << "overriding model data at " << modelName << "!\n";

	m_models[modelName] = Model();
	m_models[modelName].name = modelName;
	
	//Loading model from obj file
	static std::fstream file;
	file.open(path, std::ios::in | std::ios::binary);
	std::string line{};

	if (!file.good())
		ASSERT(true); //Could not load the obj file!

	while (std::getline(file, line)) {
		if (line.length() == 0)
			continue;
		Process(line, m_models[modelName]);
	}
	vertexNormalsIndex = 0;
	file.close();

	auto& model = m_models[modelName];
	model.vb = new VertexBuffer(model.mesh.vertices.size() * sizeof(Vertex));
	model.ib = new IndexBuffer(model.mesh.indices.data(), model.mesh.indices.size());
	model.va = new VertexArray();
	model.vb->SetLayout(layout);
	model.va->SetIndexBuffer(model.ib);
	model.vb->SetData(model.mesh.vertices.data(), model.mesh.vertices.size() * sizeof(Vertex));
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
	if(symbol.length() > 1)
		symbol.erase(symbol.length() - 1);
	Vertex v{};

	if (symbol == "#")
		return;
	else if (symbol == "v") {
		v.position = glm::vec3{ std::stof(ErasePart(' ',line)),std::stof(ErasePart(' ',line)),std::stof(line) };
		model.mesh.vertices.push_back(v);
	}
	else if (symbol == "vn") {
		model.mesh.vertices[vertexNormalsIndex].normal =
			glm::vec3{ std::stof(ErasePart(' ',line)),std::stof(ErasePart(' ',line)),std::stof(line) };
		vertexNormalsIndex++;
	}
	else if (symbol == "vt") {
		model.mesh.vertices.back().texCoords =
			glm::vec2{ std::stof(ErasePart(' ',line)),std::stof(line) };
	}
	else if (symbol == "f") {
		ProcessFace(line, model);
	}

	//switch (symbol[0])
	//{
	//case '#':
	//	return;
	//case 'v':
	//	v.position = glm::vec3{std::stof(ErasePart(' ',line)),std::stof(ErasePart(' ',line)),std::stof(line)};
	//	model.mesh.vertices.push_back(v);
	//	break;
	//case 'vn': //TODO: this propably does not work like this
	//	model.mesh.vertices[vertexNormalsIndex].normal =
	//		glm::vec3{std::stof(ErasePart(' ',line)),std::stof(ErasePart(' ',line)),std::stof(line)};
	//	vertexNormalsIndex++;
	//	break;
	//case 'vt': //TODO: same here
	//	model.mesh.vertices.back().texCoords =
	//		glm::vec2{ std::stof(ErasePart(' ',line)),std::stof(line) };
	//	break;
	//case 'f':
	//	ProcessFace(line,model);
	//	break;
	//default:
	//	break;
	//}
}

void ModelLoader::ProcessFace(std::string line, Model& model)
{
	std::string baseIndex = ErasePart(' ', line);
	std::string prevIndex = ErasePart(' ', line);
	std::string currIndex = ErasePart(' ', line);
	if (currIndex == "") {
		currIndex = line;
		line = "";
	}
	while (currIndex != "") {
		AddIndex(baseIndex,model);
		AddIndex(prevIndex,model);
		AddIndex(currIndex,model);

		prevIndex = currIndex;
		currIndex = ErasePart(' ', line);
		if (currIndex == "") {
			currIndex = line;
			line = "";
		}
	}
}

void ModelLoader::AddIndex(std::string index, Model& model)
{
	int tokenIndex = index.find_first_of('/');
	if (tokenIndex == std::string::npos) {
		model.mesh.indices.push_back(std::stoi(index) - 1);
		return;
	}
	
	std::string final = index.substr(0, tokenIndex);
	model.mesh.indices.push_back(std::stoi(final) - 1);
}
