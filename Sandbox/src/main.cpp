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
#include "Rendering/Camera.hpp"
#include "Global.hpp"
//TODO:
//vertex buffer --done
//index buffer --done
//vertex arrays --done
//batch rendering -maybe done
//geometry renderer
//camera system -implemented
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
    });

    float vertices[] = {
        //south
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        
        0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        
        //east
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,
        
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        //north                                  
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        
        1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        //west                                   
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        //top                                    
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        
        //bottom                                
        1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,
        
        1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
	};

    //float vertices[] = {
    //    0.f,0.f,0.f,
    //    0.f,1.f,0.f,
    //    1.f,1.f,0.f,
    //    1.f,0.f,0.f,
    //};

    VertexBuffer* vb = new VertexBuffer(vertices,sizeof(vertices));
    vb->SetLayout(layout);

    uint32_t indicies[36] = {
        0,1,2, //south
        3,4,5,

        6,7,8, //east
        9,10,11,

        12,13,14, //north
        15,16,17,

        18,19,20, //west
        21,22,23,

        24,25,26, //top
        27,28,29,

        30,31,32, //bottom
        33,34,35,
    };
    //uint32_t indicies[] = {
    //    0,1,2,
    //    2,3,0,
    //};

    IndexBuffer* ib = new IndexBuffer(indicies,sizeof(indicies));

    VertexArray va;
    va.AddVertexBuffer(vb);
    va.SetIndexBuffer(ib);

    renderer.Draw(&va);

    PerspectiveCamera camera(90.f,float(window::size.x)/float(window::size.y),0.1f,100.f);
    //OrthographicCamera camera(-2.f,2.f,-2.f,2.f);
    camera.SetUpAxis({ 0.f,1.0f,0.f });
    camera.SetPosition({ -5.f,0.f,-5.f });
    renderer.SetCamera(camera);
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