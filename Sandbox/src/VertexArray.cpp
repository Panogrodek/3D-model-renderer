#include "pch.h"
#include "Rendering/VertexArray.hpp"

#include <GLEW/glew.h>

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
	switch (type)
	{
	case ShaderDataType::Float:		return GL_FLOAT;
	case ShaderDataType::Float2:	return GL_FLOAT;
	case ShaderDataType::Float3:	return GL_FLOAT;
	case ShaderDataType::Float4:	return GL_FLOAT;
	case ShaderDataType::Mat3:		return GL_FLOAT;
	case ShaderDataType::Mat4:		return GL_FLOAT;
	case ShaderDataType::Int:		return GL_INT;
	case ShaderDataType::Int2:		return GL_INT;
	case ShaderDataType::Int3:		return GL_INT;
	case ShaderDataType::Int4:		return GL_INT;
	case ShaderDataType::Bool:		return GL_BOOL;
	}

	ASSERT(true); //Unknown ShaderDataType!
	return 0;
}

VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &m_RendererID);
}
VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const VertexBuffer* vertexBuffer)
{
	ASSERT(vertexBuffer->GetLayout().GetElements().empty()); //Vertex buffer has no layout!

	glBindVertexArray(m_RendererID);
	vertexBuffer->Bind();

	uint32_t index = 0;
	const auto& layout = vertexBuffer->GetLayout();
	for (const auto& element : layout) {

		glEnableVertexAttribArray(index);
		glVertexAttribPointer(
			index,
			element.GetComponentCount(),
			ShaderDataTypeToOpenGLBaseType(element.Type),
			element.Normalised ? GL_TRUE : GL_FALSE,
			vertexBuffer->GetLayout().GetStride(),
			(const void*)element.Offset);
		index++;
	}

	m_VertexBuffers.push_back(vertexBuffer);
}

void VertexArray::SetIndexBuffer(const IndexBuffer* indexBuffer)
{
	glBindVertexArray(m_RendererID);
	indexBuffer->Bind();

	m_IndexBuffer = indexBuffer;
}
