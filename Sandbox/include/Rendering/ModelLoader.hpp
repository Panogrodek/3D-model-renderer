#pragma once
#include <GLM/glm.hpp>
#include "Rendering/VertexArray.hpp"

inline std::string ErasePart(char symbol, std::string& line);

struct Vertex {
	glm::vec3 position{};
	glm::vec3 normal{}; //TODO: implement
	glm::vec2 texCoords{}; //TODO: implement

	glm::vec4 color{}; //TODO: debug only
	float texIndex{}; //TODO: implement or not
};

struct Mesh {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	//TODO: add material data
};

namespace priv {
	class ModelLoader;
	class GeometryRenderer;
}

struct Model { //this can be upgraded to include textures and other things 
	~Model() {
		if(vb != nullptr) delete vb;
		if(ib != nullptr) delete ib;
		if(va != nullptr) delete va;
	};
	std::string name;

	glm::mat4 transform{1.0f};
	VertexArray* va;
private:
	friend class priv::ModelLoader;
	friend class priv::GeometryRenderer;
	VertexBuffer* vb;
	IndexBuffer* ib;
	Mesh mesh;
};

namespace priv {
	class ModelLoader {
	public:
		void Load(std::string path, std::string modelName);

		Model& GetModel(std::string name);
	private:
		void Process(std::string line, Model& model);

		std::unordered_map<std::string, Model> m_models;
	};
}

inline extern priv::ModelLoader modelLoader{};