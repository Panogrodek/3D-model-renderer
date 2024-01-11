#pragma once

#include <GLM/glm.hpp>
#include <GLM/ext/matrix_transform.hpp>
#include <GLM/ext/matrix_clip_space.hpp>

class Camera {
public:
	Camera();

	//view
	void SetPosition(const glm::vec3& position);
	void SetDirection(const glm::vec3& direction);
	void SetUpAxis(const glm::vec3& upAxis);

	const glm::vec3& GetPosition();
	const glm::vec3& GetDirection();
	const glm::vec3& GetUpAxis();

	void LookAt(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& up);

	//rotation
	float GetPitch();
	float GetYaw();
	float GetRoll();

	void SetPitch(float pitch);
	void SetYaw	 (float yaw);
	void SetRoll (float roll);

	//camera
	void SetView(const glm::mat4& view);
	void SetProjection(const glm::mat4& projection);
	void SetViewProjection(const glm::mat4& viewProjection);

	void Bind();

	const glm::mat4& GetView();
	const glm::mat4& GetProjection();
	const glm::mat4& GetViewProjection(); //we use this for shaders
protected:
	virtual void UpdateCameraTransform();
	virtual void UpdateCameraRotation();

	bool m_updateCameraTransform = true;
	bool m_updateCameraRotation  = false;

	glm::vec3 m_position{};
	glm::vec3 m_direction{ 0.f,0.f,-1.f };
	glm::vec3 m_upAxis{};

	glm::mat4 m_view{};
	glm::mat4 m_projection{};
	glm::mat4 m_viewProjection{};

	float m_pitch{}; //x axis
	float m_yaw{};   //y axis
	float m_roll{};  //z axis
};

class OrthographicCamera : public Camera {
public:
	OrthographicCamera() {};
	OrthographicCamera(float left, float right, float bottom, float top) {
		m_projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	};

	void SetProjection(float left, float right, float bottom, float top) {
		m_updateCameraTransform = true;
		m_projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	}
};

class PerspectiveCamera : public Camera {
public:
	PerspectiveCamera() {};
	PerspectiveCamera(float fovDegrees, float aspectRatio, float znear, float zfar) {
		m_projection = glm::perspective(glm::radians(fovDegrees), aspectRatio, znear, zfar);
	};

	void SetProjection(float fovDegrees, float aspectRatio, float znear, float zfar) {
		m_updateCameraTransform = true;
		m_projection = glm::perspective(glm::radians(fovDegrees), aspectRatio, znear, zfar);
	}
};