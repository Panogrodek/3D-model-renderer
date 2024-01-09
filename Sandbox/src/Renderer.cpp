#include "pch.h"
#include "Rendering/Renderer.hpp"
#include "Global.hpp"

#include "Rendering/GeometryRenderer.hpp"

//IMGUI TODO:Move
#include <imgui.h>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLM/gtc/type_ptr.hpp>

using namespace priv;

void Renderer::InitGL()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    m_window = glfwCreateWindow(window::size.x, window::size.y, "3D Model Rendering", nullptr, nullptr);
    glfwMakeContextCurrent(m_window);

    //// Set the required callback functions
    //glfwSetKeyCallback(window, key_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(m_window, &width, &height);
    glViewport(0, 0, width, height);

    //mouse input
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    //TODO: temporary
    shader = new Shader("res/shaders/FlatColor.glsl"); 

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(renderer.GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 430");
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    geometryRenderer.Init();
}

void Renderer::Destroy()
{
    glfwTerminate();

    //TODO: move
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Renderer::BeginDraw()
{
    // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
    glfwPollEvents(); //TODO: this NEEDS to be moved into application.hpp of some sort

    glClearColor(window::clear_color.r, window::clear_color.g, window::clear_color.b, window::clear_color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render
    // Clear the colorbuffer

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Renderer::EndDraw()
{
    ImGui::Begin("Demo window");
    //ImGui::SliderFloat3("position", glm::value_ptr(position), -10.f, 10.f);
    ImGui::End();

    //s_currentCamera.SetPosition(position);
    //s_currentCamera.SetYaw(yaw);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap the screen buffers
    glfwSwapBuffers(renderer.GetWindow());
}

void Renderer::Draw(const VertexArray* va)
{
    m_vertexArrays.push_back(va);
}

void Renderer::SetCamera(const ::Camera& camera)
{
    m_currentCamera = camera;
}

Camera& Renderer::GetCurrentCamera()
{
    return m_currentCamera;
}

glm::vec2 priv::Renderer::GetMousePosition()
{
    double xpos, ypos;
    glfwGetCursorPos(m_window, &xpos, &ypos);
    m_mousePos = glm::vec2(float(xpos), float(ypos));
    return m_mousePos;
}

void Renderer::RenderPass()
{
    
    
    Flush();
    
    //glm::vec3 position = m_currentCamera.GetPosition();
    //float yaw = m_currentCamera.GetYaw();
    //
    //glm::vec3 cameraFront = m_currentCamera.GetDirection();
    //glm::vec3 cameraUp = { 0.f,1.0f,0.f };
    //static float cameraSpeed = 0.025f; // adjust accordingly
}

void Renderer::Flush()
{
    //for (auto& va : m_vertexArrays) { //this is not a batch rendering approach, this needs to be fixed


    //    //Rendering
    //    va->Bind();
    //    uint32_t count = va->GetIndexBuffer()->GetCount();
    //    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);

    //    va->Unbind();
    //}
    shader->Bind();
    shader->SetMat4("u_ViewProjection", m_currentCamera.GetViewProjection()); //this could have been done better
    shader->Unbind();

    m_vertexArrays.clear(); //TODO: uncomment
}

GLFWwindow* const Renderer::GetWindow()
{
    return m_window;
}
