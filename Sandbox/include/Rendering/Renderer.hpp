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

		::Camera& GetCurrentCamera();

		glm::vec2 GetMousePosition();

		GLFWwindow* const GetWindow();

		void RenderPass(); //TODO: move into private when Application.hpp exists
	private:
		void Flush();

		GLFWwindow* m_window;
		std::vector<const VertexArray*> m_vertexArrays;
		Shader* shader; //this is temporary

		glm::vec2 m_mousePos{};

		::Camera m_currentCamera;
	};
}

inline priv::Renderer renderer{};