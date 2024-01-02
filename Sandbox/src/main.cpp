#include <iostream>
#include "pch.h"
// GLEW
#include <GLEW/glew.h>

// GLFW
#include <GLFW/glfw3.h>

//IMGUI
#include <IMGUI/imgui.h>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

//RENDERING
#include "Rendering/Shader.hpp"
#include "Rendering/VertexArray.hpp"

//TODO:
//vertex buffer --done
//index buffer --done
//vertex arrays --done
//batch rendering
//camera system
//IMGUI --done


// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// The MAIN function, from here we start the application and run the game loop
int main()
{
    IMGUI_CHECKVERSION();
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 430");
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();


    // Build and compile our shader program
    // Vertex shader
    Shader shader("res/shaders/FlatColor.glsl");
    //GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    //glCompileShader(vertexShader);
    //// Check for compile time errors
    //GLint success;
    //GLchar infoLog[512];
    //glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    //if (!success)
    //{
    //    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    //    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    //}
    //// Fragment shader
    //GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    //glCompileShader(fragmentShader);
    //// Check for compile time errors
    //glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    //if (!success)
    //{
    //    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    //    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    //}
    //// Link shaders
    //GLuint shaderProgram = glCreateProgram();
    //glAttachShader(shaderProgram, vertexShader);
    //glAttachShader(shaderProgram, fragmentShader);
    //glLinkProgram(shaderProgram);
    //// Check for linking errors
    //glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    //if (!success) {
    //    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    //    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    //}
    //glDeleteShader(vertexShader);
    //glDeleteShader(fragmentShader);


    // Set up vertex data (and buffer(s)) and attribute pointers
    // We add a new set of vertices to form a second triangle (a total of 6 vertices); the vertex attribute configuration remains the same (still one 3-float position vector per vertex)
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

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        shader.Bind();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Rendering
        va.Bind();
        uint32_t count = va.GetIndexBuffer()->GetCount();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        va.Unbind();

        ImGui::Begin("Demo window");
        ImGui::Button("Hello!");
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        shader.Unbind();

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}