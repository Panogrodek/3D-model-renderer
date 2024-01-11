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
		
		void BeginDraw();
		void EndDraw();

		void SetCamera(const ::Camera& camera);

		::Camera& GetCurrentCamera();

		glm::vec2 GetMousePosition();

		GLFWwindow* const GetWindow();

		void UpdateImguiPosition();
	private:
		GLFWwindow* m_window;
		glm::vec2 m_mousePos{};

		::Camera m_currentCamera;
	};
}

inline priv::Renderer renderer{};