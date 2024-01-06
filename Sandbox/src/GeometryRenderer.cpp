#include "pch.h"
#include "Rendering/GeometryRenderer.hpp"

using namespace priv;

void GeometryRenderer::Init()
{
    data.GeometryShader = new Shader("res/shaders/FlatColor.glsl");

	//initializing the data
    BufferLayout layout({
    { ShaderDataType::Float3, "a_Position" },
    { ShaderDataType::Float3, "a_Normal" },
    { ShaderDataType::Float2, "a_TexCoords" },
    { ShaderDataType::Float4, "a_Color" },
    { ShaderDataType::Float,  "a_TexIndex" },
    });

    data.VertexArray = new VertexArray;
    data.VertexBuffer = new VertexBuffer(MAX_VERTEX_COUNT * sizeof(Vertex));
    data.VertexBuffer->SetLayout(layout);

    uint32_t offset = 0;
    uint32_t* geometryIndicies = new uint32_t[MAX_INDEX_COUNT];
    for (uint32_t i = 0; i < MAX_INDEX_COUNT; i += 6) { //TODO: change

        geometryIndicies[i + 0] = offset + 0;
        geometryIndicies[i + 1] = offset + 1;
        geometryIndicies[i + 2] = offset + 2;

        geometryIndicies[i + 3] = offset + 2;
        geometryIndicies[i + 4] = offset + 3;
        geometryIndicies[i + 5] = offset + 0;

        offset += 4;
    }

    data.IndexBuffer = new IndexBuffer(geometryIndicies, MAX_INDEX_COUNT);
    data.VertexArray->SetIndexBuffer(data.IndexBuffer);
    data.VertexArray->AddVertexBuffer(data.VertexBuffer);

    delete[] geometryIndicies;

    data.VertexBufferBase = new Vertex[MAX_VERTEX_COUNT];
    data.VertexBufferPtr = data.VertexBufferBase;
}

void GeometryRenderer::DrawModel(Model& model)
{
    for (auto& vert : model.mesh.vertices) {
        *data.VertexBufferPtr = vert;
        data.VertexBufferPtr++;
    }

    data.IndexBuffer->SetData(model.mesh.indices.data(), model.mesh.indices.size());
}

void GeometryRenderer::Destroy()
{
    delete data.VertexArray;
    delete data.VertexBuffer;
    delete data.IndexBuffer;
    delete data.GeometryShader;
    delete data.VertexBufferBase;
}

void GeometryRenderer::Flush()
{
    uint32_t dataSize = (uint8_t*)data.VertexBufferPtr - (uint8_t*)data.VertexBufferBase;
    data.VertexBuffer->SetData(data.VertexBufferBase, dataSize);

    data.VertexArray->Bind();
    uint32_t count = data.VertexArray->GetIndexBuffer()->GetCount();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
    data.VertexArray->Unbind();

    data.VertexBufferPtr = data.VertexBufferBase;
}
