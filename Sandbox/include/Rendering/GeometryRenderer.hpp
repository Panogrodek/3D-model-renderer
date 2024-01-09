#pragma once

#include "Renderer.hpp"
#include "ModelLoader.hpp"

namespace priv {
	//constexpr int MAX_QUAD_COUNT = 100000;
	//constexpr int MAX_VERTEX_COUNT = MAX_QUAD_COUNT * 4;
	//constexpr int MAX_INDEX_COUNT = MAX_QUAD_COUNT * 6;

	//struct GeometryRenderData {
	//	VertexArray* VertexArray;
	//	VertexBuffer* VertexBuffer;
	//	IndexBuffer* IndexBuffer;

	//	Shader* GeometryShader;

	//	Vertex* VertexBufferBase = nullptr;
	//	Vertex* VertexBufferPtr = nullptr;
	//};

	class GeometryRenderer {
	public:
		void Init();
		void DrawModel(Model& model);

		void Destroy();
	private:
		friend class Renderer;
		Shader* m_GeometryShader;
	};
}

inline priv::GeometryRenderer geometryRenderer{};