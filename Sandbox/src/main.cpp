#include <iostream>
#include "pch.h"
// GLEW
#include <GLEW/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "Rendering/Renderer.hpp"



//RENDERING
#include "Rendering/Shader.hpp"
#include "Rendering/VertexArray.hpp"

//TODO:
//vertex buffer --done
//index buffer --done
//vertex arrays --done
//batch rendering -maybe done
//geometry renderer
//camera system -currently using imgui
//IMGUI --done


// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// The MAIN function, from here we start the application and run the game loop
int main()
{
    renderer.InitGL();

    // Build and compile our shader program
    // Vertex shader
    Shader shader("res/shaders/FlatColor.glsl");
    BufferLayout layout({
        { ShaderDataType::Float3, "a_Position" },
        { ShaderDataType::Float4, "a_Color" },
    });

    float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Left 
        -0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // Right
        -0.45f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Top 
    };

    VertexBuffer* vb = new VertexBuffer(firstTriangle,sizeof(firstTriangle));
    vb->SetLayout(layout);

    uint32_t indicies[] = {
        0,1,2
    };

    IndexBuffer* ib = new IndexBuffer(indicies,sizeof(indicies));

    VertexArray va;
    va.AddVertexBuffer(vb);
    va.SetIndexBuffer(ib);

    renderer.Draw(&va);

    // Game loop
    while (!glfwWindowShouldClose(renderer.GetWindow()))
    {
        renderer.RenderPass();
    }
    renderer.Destroy();

    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}