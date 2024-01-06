#include "pch.h"
#include "Core/Application.hpp"

#include "Rendering/Renderer.hpp"
#include "Rendering/GeometryRenderer.hpp"
#include "Global.hpp"
#include "Rendering/ModelLoader.hpp"

Application::Application()
{
	renderer.InitGL();
    //va = new VertexArray;

    //TODO: temp
    // Vertex shader

    //Shader shader("res/shaders/FlatColor.glsl");
    //BufferLayout layout({
    //    { ShaderDataType::Float3, "a_Position" },
    //    { ShaderDataType::Float3, "a_Normal" },
    //    { ShaderDataType::Float2, "a_TexCoords" },
    //    { ShaderDataType::Float4, "a_Color" },
    //    { ShaderDataType::Float,  "a_TexIndex" },
    //});

    modelLoader.Load("res/obj/teapot.obj","teapot");

    //VertexBuffer* vb = new VertexBuffer(modelLoader.GetModel("teapot")
    //    ,sizeof(modelLoader.GetModel("teapot").mesh.vertices.data()));
    //vb->SetLayout(layout);

    //uint32_t indicies[36] = {
    //    0,1,2, //south
    //    3,4,5,

    //    6,7,8, //east
    //    9,10,11,

    //    12,13,14, //north
    //    15,16,17,

    //    18,19,20, //west
    //    21,22,23,

    //    24,25,26, //top
    //    27,28,29,

    //    30,31,32, //bottom
    //    33,34,35,
    //};

    //IndexBuffer* ib = new IndexBuffer(indicies, sizeof(indicies));


    //va->AddVertexBuffer(vb);
    //va->SetIndexBuffer(ib);

    camera = PerspectiveCamera(45.f, float(window::size.x) / float(window::size.y), 0.1f, 100.f);
    //OrthographicCamera camera(-2.f,2.f,-2.f,2.f);
    camera.SetUpAxis({ 0.f,1.0f,0.f });
    camera.SetPosition({ 0.f,0.f,-5.f });
    camera.SetYaw(90.f);
}

Application::~Application()
{
    renderer.Destroy();
    geometryRenderer.Destroy();
}

void Application::Run()
{
    while (!glfwWindowShouldClose(renderer.GetWindow()))
    {
        if (dt > 0.25f) //we are setting max delta time value to avoid spiraling into void
            dt = 0.25f;

        Update();
        Render();

        m_timeAccumulator += dt;

        while (m_timeAccumulator >= m_physicsTimeStep) {
            m_timeAccumulator -= m_physicsTimeStep;
            fdt = m_physicsTimeStep; //TODO: this is incorrect. This doesn't need to be changed because there are no physics.

            FixedUpdate();
        }
        
        float currentFrame = glfwGetTime();
        dt = currentFrame - m_lastFrame;
        m_lastFrame = currentFrame;
    }
}

void Application::Update()
{
    controller.Update(camera);
}

void Application::Render()
{
    renderer.SetCamera(camera);
    
    geometryRenderer.DrawModel(modelLoader.GetModel("teapot"));

    renderer.RenderPass();
}

void Application::FixedUpdate()
{
}
