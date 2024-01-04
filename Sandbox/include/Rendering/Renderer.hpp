#pragma once
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "Rendering/Shader.hpp"
#include "Rendering/VertexArray.hpp"
#include "Rendering/Camera.hpp"

namespace priv {
	class Renderer {
	public:
		void InitGL();
		void Destroy();
		
		void Draw(const VertexArray* va);
		void SetCamera(const ::Camera& camera);

		GLFWwindow* const GetWindow();

		void RenderPass(); //TODO: move into private when Application.hpp exists
	private:
		void Flush();

		GLFWwindow* s_window;
		std::vector<const VertexArray*> s_vertexArrays;
		Shader* shader; //this is temporary

		::Camera s_currentCamera;
	};
}

inline extern priv::Renderer renderer{};