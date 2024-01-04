#include "pch.h"
#include "Rendering/Camera.hpp"
#include "Global.hpp"

Camera::Camera()
{
}

Camera::Camera(float fovDegrees, float aspectRatio, float znear, float zfar)
{
	m_updateCameraTransform = true;
	m_projection = glm::perspective(glm::radians(fovDegrees), aspectRatio, znear, zfar);
}

void Camera::SetPosition(const glm::vec3& position)
{
	m_position = position;
	m_updateCameraTransform = true;
}

void Camera::SetDirection(const glm::vec3& direction)
{
	m_direction = direction;
	m_updateCameraTransform = true;
}

void Camera::SetUpAxis(const glm::vec3& upAxis)
{
	m_upAxis = upAxis;
	m_updateCameraTransform = true;
}

const glm::vec3& Camera::GetPosition()
{
	return m_position;
}

const glm::vec3& Camera::GetDirection()
{
	UpdateCameraRotation();
	return m_direction;
}

const glm::vec3& Camera::GetUpAxis()
{
	return m_upAxis;
}

void Camera::LookAt(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& upAxis)
{
	m_view = glm::lookAt(position,position + direction,upAxis);
	m_updateCameraTransform = true;
}

float Camera::GetPitch()
{
	return m_pitch;
}

float Camera::GetYaw()
{
	return m_yaw;
}

float Camera::GetRoll()
{
	return m_roll;
}

void Camera::SetPitch(float pitch)
{
	m_pitch = pitch;
	m_updateCameraRotation = true;
}

void Camera::SetYaw(float yaw)
{
	m_yaw = yaw;
	m_updateCameraRotation = true;
}

void Camera::SetRoll(float roll)
{
	m_roll = roll;
	m_updateCameraRotation = true;
}

void Camera::SetView(const glm::mat4& view)
{
	m_view = view;
	m_updateCameraTransform = true;
}

void Camera::SetProjection(const glm::mat4& projection)
{
	m_projection = projection;
	m_updateCameraTransform = true;
}

void Camera::SetViewProjection(const glm::mat4& viewProjection)
{
	m_viewProjection = viewProjection;
	m_updateCameraTransform = true;
}

const glm::mat4& Camera::GetView()
{
	UpdateCameraTransform();
	return m_view;
}

const glm::mat4& Camera::GetProjection()
{
	UpdateCameraTransform();
	return m_projection;
}

const glm::mat4& Camera::GetViewProjection()
{
	UpdateCameraTransform();
	return m_viewProjection;
}

void Camera::UpdateCameraTransform()
{
	if (!m_updateCameraTransform)
		return;

	UpdateCameraRotation();

	m_view = glm::lookAt(m_position, m_position + m_direction, m_upAxis);
	m_viewProjection = m_projection * glm::inverse(m_view);

	m_updateCameraTransform = false;
}

void Camera::UpdateCameraRotation()
{
	if (!m_updateCameraRotation)
		return;

	m_direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_direction.y = sin(glm::radians(m_pitch));
	m_direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

	m_direction = glm::normalize(m_direction);

	m_updateCameraRotation = false;
}
