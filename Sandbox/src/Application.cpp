#include "pch.h"
#include "Core/Application.hpp"

#include "Rendering/Renderer.hpp"
#include "Rendering/GeometryRenderer.hpp"
#include "Global.hpp"
#include "Rendering/ModelLoader.hpp"

Application::Application()
{
	renderer.InitGL();
    //modelLoader.Load("res/obj/cube.obj","cube");
    modelLoader.Load("res/obj/cube.obj","pyramid");
    //modelLoader.GetModel("cube").transform = glm::translate(glm::mat4(1.0f), {0.f,-2.5f,0.f});

    camera = PerspectiveCamera(45.f, float(window::size.x) / float(window::size.y), 0.1f, 100.f);
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
    renderer.BeginDraw();
    camera.Bind();

    geometryRenderer.DrawModel(modelLoader.GetModel("pyramid"));
    //geometryRenderer.DrawModel(modelLoader.GetModel("cube"));

    renderer.EndDraw();
}

void Application::FixedUpdate()
{
}
