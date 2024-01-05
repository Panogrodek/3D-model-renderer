#include "pch.h"
#include "Rendering/CameraController.hpp"
#include "Rendering/Renderer.hpp"

#include "Global.hpp"


void CameraController::Update(Camera& camera)
{
    UpdateKeyboard(camera);
    UpdateMouse(camera);
}

void CameraController::UpdateMouse(Camera& camera)
{
    glm::vec2 mousePos = renderer.GetMousePosition();
    if (glfwGetMouseButton(renderer.GetWindow(), GLFW_MOUSE_BUTTON_2) != GLFW_PRESS) {
        m_lockMouse = true;
        
        float yaw = camera.GetYaw();
        float pitch = camera.GetPitch();
        m_endYaw = yaw;
        m_endPitch = pitch;
        return;
    }

    if (m_lockMouse) {
        m_lockMouse = false;
        LockMouseCursorPos();
        return;
    }

    float yaw = camera.GetYaw();
    float pitch = camera.GetPitch();

    glm::vec2 offset = mousePos - glm::vec2(window::size);

    offset *= m_mouseSensitivity * dt;
    
    if (offset != glm::vec2(0.f))
        offset = glm::normalize(offset);

    m_endYaw += offset.x; 
    m_endPitch -= offset.y; //whops

    // change this
    if (m_endPitch > 89.0f)
        m_endPitch = 89.0f;
    if (m_endPitch < -89.0f)
        m_endPitch = -89.0f;
    
    float newYaw = glm::mix(yaw, m_endYaw, m_mouseLerpSensitivity * dt);
    float newPitch = glm::mix(pitch, m_endPitch, m_mouseLerpSensitivity * dt);

    camera.SetYaw(newYaw);
    camera.SetPitch(newPitch);

    LockMouseCursorPos();
}

void CameraController::UpdateKeyboard(Camera& camera)
{
    GLFWwindow* window = renderer.GetWindow();
    glm::vec3 cameraUp = camera.GetUpAxis();
    glm::vec3 position = camera.GetPosition();
    
    glm::vec3 front = camera.GetDirection();
    front.y = 0.f;
    front = glm::normalize(front);

    glm::vec3 left = glm::cross(camera.GetDirection(),cameraUp);
    left = glm::normalize(left);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) //front
        position += m_cameraSpeed * front * fdt;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) //back
        position -= m_cameraSpeed * front * fdt;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) //right
        position += m_cameraSpeed * left * fdt;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) //left
        position -= m_cameraSpeed * left * fdt;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) //up
        position += m_cameraSpeed * cameraUp * fdt;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) //down
        position -= m_cameraSpeed * cameraUp * fdt;

    camera.SetPosition(position);
    //if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    //    yaw -= 0.5f;
    //if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    //    yaw += 0.5f;
}

void CameraController::LockMouseCursorPos()
{
    glfwSetCursorPos(renderer.GetWindow(),double(window::size.x),double(window::size.y));
}
