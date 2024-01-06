#pragma once
#include <GLM/glm.hpp>

inline std::string ErasePart(char symbol, std::string& line);

struct Vertex {
	glm::vec3 position{};
	glm::vec3 normal{}; //TODO: implement
	glm::vec2 texCoords{}; //TODO: implement

	glm::vec4 color{}; //TODO: debug only
	float texIndex{}; //TODO: implement or not
};

//struct Triangle {
//	Vertex vertices[3];
//};
//
//struct Quad {
//	Vertex vertices[4];
//};

struct Mesh {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	//TODO: add material data
};

struct Model { //this can be upgraded to include textures and other things 
	Mesh mesh;
	std::string name;

	//float* GetVertices();
	//uint32_t GetVerticesSize();
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