#pragma once
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "Rendering/Shader.hpp"
#include "Rendering/VertexArray.hpp"

namespace priv {
	class Renderer {
	public:
		static void InitGL();
		static void Destroy();
		
		static void Draw(const VertexArray* va);

		static GLFWwindow* const GetWindow();

		static void RenderPass(); //TODO: move into private when Application.hpp exists
	private:
		static void Flush();

		static GLFWwindow* s_window;
		static std::vector<const VertexArray*> s_vertexArrays;
		static Shader* shader; //this is temporary
	};
}

extern priv::Renderer renderer;