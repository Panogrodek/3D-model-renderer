#pragma once

#include "Renderer.hpp"
#include "ModelLoader.hpp"

namespace priv {
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