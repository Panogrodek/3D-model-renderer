#include "pch.h"
#include "Rendering/Renderer.hpp"
#include "Global.hpp"

//IMGUI TODO:Move
#include <imgui.h>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLM/gtc/type_ptr.hpp>

using namespace priv;

GLFWwindow* Renderer::s_window;
std::vector<const VertexArray*> Renderer::s_vertexArrays;
Shader* Renderer::shader;

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
    s_window = glfwCreateWindow(window::size.x, window::size.y, "3D Model Rendering", nullptr, nullptr);
    glfwMakeContextCurrent(s_window);

    //// Set the required callback functions
    //glfwSetKeyCallback(window, key_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(s_window, &width, &height);
    glViewport(0, 0, width, height);

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
}

void Renderer::Destroy()
{
    glfwTerminate();

    //TODO: move
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Renderer::Draw(const VertexArray* va)
{
    s_vertexArrays.push_back(va);
}

void Renderer::RenderPass()
{
    static glm::vec4 move;
    // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
    glfwPollEvents(); //TODO: this NEEDS to be moved into application.hpp of some sort

    glClearColor(window::clear_color.r, window::clear_color.g, window::clear_color.b, window::clear_color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render
    // Clear the colorbuffer

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    shader->Bind();
    shader->SetFloat4("u_ViewProjection", move);
    shader->Unbind();
    
    Flush();

    ImGui::Begin("Demo window");
    ImGui::SliderFloat4("move",glm::value_ptr(move),0.f,10.f);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap the screen buffers
    glfwSwapBuffers(renderer.GetWindow());
}

void Renderer::Flush()
{
    for (auto& va : s_vertexArrays) { //this is not a batch rendering approach, this needs to be fixed
        shader->Bind();

        //Rendering
        va->Bind();
        uint32_t count = va->GetIndexBuffer()->GetCount();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        va->Unbind();

        shader->Unbind();
    }

    //s_vertexArrays.clear(); //TODO: uncomment
}

GLFWwindow* const Renderer::GetWindow()
{
    return s_window;
}
