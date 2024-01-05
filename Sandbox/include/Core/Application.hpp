#pragma once

//TODO: delete or move to CameraData.hpp
#include "Rendering/Camera.hpp"
#include "Rendering/CameraController.hpp"
#include "Rendering/VertexArray.hpp" //TODO: remove

class Application {
public:
	Application();
	~Application();

	void Run();
private:
	void Update();
	void Render();
	void FixedUpdate();

	float m_timeAccumulator = 0.f;
	float m_physicsTimeStep = 0.05f;
	float m_lastFrame = 0.f;

	//TODO: temp
	VertexArray* va;

	PerspectiveCamera camera;
	CameraController controller;
};