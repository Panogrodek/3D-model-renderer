#pragma once
#include <GLM/glm.hpp>
#include "Rendering/VertexArray.hpp"

inline std::string ErasePart(char symbol, std::string& line);

struct Vertex {
	glm::vec3 position{};
	glm::vec3 normal{0.f,0.f,1.f}; //TODO: implement /not to implement
	glm::vec2 texCoords{}; //TODO: implement /not to implement

	glm::vec4 color{}; //TODO: debug only /not to implement
	float texIndex{}; //TODO: implement /not to implement
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

struct Model { //this can be upgraded to include textures and other things /not to implement
	~Model() {
		if(vb != nullptr) delete vb;
		if(ib != nullptr) delete ib;
		if(va != nullptr) delete va;
	};
	std::string name;

	glm::mat4 transform{1.0f};
	glm::vec3 rotation{ 0.f };
	glm::vec3 scale{ 1.0f };
	VertexArray* va;
	Mesh mesh;
private:
	friend class priv::ModelLoader;
	friend class priv::GeometryRenderer;
	VertexBuffer* vb;
	IndexBuffer* ib;
};

namespace priv {
	class ModelLoader {
	public:
		void Load(std::string path, std::string modelName);

		Model& GetModel(std::string name);
	private:
		void Process(std::string line, Model& model);
		void ProcessFace(std::string line, Model& model);

		void AddIndex(std::string index, Model& model);
		int vertexNormalsIndex = 0;
		std::unordered_map<std::string, Model> m_models;
	};
}

inline extern priv::ModelLoader modelLoader{};