#include "pch.h"
#include "Rendering/GeometryRenderer.hpp"
#include "Global.hpp"

using namespace priv;

void GeometryRenderer::Init()
{
    m_GeometryShader = new Shader("res/shaders/FlatColor.glsl");
}

void GeometryRenderer::DrawModel(Model& model)
{
    m_GeometryShader->Bind();
    auto& camera = renderer.GetCurrentCamera();
    m_GeometryShader->SetMat4("u_ViewProjection", camera.GetViewProjection()); 
    m_GeometryShader->SetMat4("u_Transform", model.transform); 
    m_GeometryShader->SetFloat3("u_LightDir", lightDirection);

    model.va->Bind();
    uint32_t count = model.va->GetIndexBuffer()->GetCount();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    model.va->Unbind();

    m_GeometryShader->Unbind();
}

void GeometryRenderer::Destroy()
{
    delete m_GeometryShader;
}
