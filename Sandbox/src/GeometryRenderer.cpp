#include "pch.h"
#include "Rendering/GeometryRenderer.hpp"

using namespace priv;

void GeometryRenderer::Init()
{
    m_GeometryShader = new Shader("res/shaders/FlatColor.glsl");

	////initializing the data
 //   BufferLayout layout({
 //   { ShaderDataType::Float3, "a_Position" },
 //   { ShaderDataType::Float3, "a_Normal" },
 //   { ShaderDataType::Float2, "a_TexCoords" },
 //   { ShaderDataType::Float4, "a_Color" },
 //   { ShaderDataType::Float,  "a_TexIndex" },
 //   });

 //   data.VertexArray = new VertexArray;
 //   data.VertexBuffer = new VertexBuffer(MAX_VERTEX_COUNT * sizeof(Vertex));
 //   data.VertexBuffer->SetLayout(layout);

 //   uint32_t offset = 0;
 //   uint32_t* geometryIndicies = new uint32_t[MAX_INDEX_COUNT];
 //   for (uint32_t i = 0; i < MAX_INDEX_COUNT; i += 6) { //TODO: change

 //       geometryIndicies[i + 0] = offset + 0;
 //       geometryIndicies[i + 1] = offset + 1;
 //       geometryIndicies[i + 2] = offset + 2;

 //       geometryIndicies[i + 3] = offset + 2;
 //       geometryIndicies[i + 4] = offset + 3;
 //       geometryIndicies[i + 5] = offset + 0;

 //       offset += 4;
 //   }

 //   data.IndexBuffer = new IndexBuffer(geometryIndicies, MAX_INDEX_COUNT);
 //   data.VertexArray->SetIndexBuffer(data.IndexBuffer);
 //   data.VertexArray->AddVertexBuffer(data.VertexBuffer);

 //   delete[] geometryIndicies;

 //   data.VertexBufferBase = new Vertex[MAX_VERTEX_COUNT];
 //   data.VertexBufferPtr = data.VertexBufferBase;
}

void GeometryRenderer::DrawModel(Model& model)
{
    m_GeometryShader->Bind();
    auto& camera = renderer.GetCurrentCamera();
    m_GeometryShader->SetMat4("u_ViewProjection", camera.GetViewProjection()); 
    m_GeometryShader->SetMat4("u_Transform", model.transform); 
    m_GeometryShader->SetFloat3("u_LightDir",{0.f,1.5f,0.f});

    model.va->Bind();
    uint32_t count = model.va->GetIndexBuffer()->GetCount();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
    model.va->Unbind();

    m_GeometryShader->Unbind();
}

void GeometryRenderer::Destroy()
{
    delete m_GeometryShader;
}
