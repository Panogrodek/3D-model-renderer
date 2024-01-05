#pragma once
#include "Camera.hpp"

class CameraController {
public:
	void Update(Camera& camera);
	void UpdateMouse(Camera& camera);
	void UpdateKeyboard(Camera& camera);
		
private:
	void LockMouseCursorPos();
	float m_cameraSpeed = 0.1f;

	float m_mouseSensitivity = 15.f; //this variable sets the speed of camera rotation
	float m_mouseLerpSensitivity = 10.f; //this variable sets the time it takes to complete the camera rotation

	float m_endYaw{};
	float m_endPitch{};
	float t{};

	bool m_lockMouse = false;
};