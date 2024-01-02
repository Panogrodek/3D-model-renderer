#pragma once
#include "Rendering/Buffer.hpp"

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddVertexBuffer(const VertexBuffer* vertexBuffer);
	void SetIndexBuffer(const  IndexBuffer* indexBuffer);

	const std::vector<const VertexBuffer*>& GetVertexBuffers() const { return m_VertexBuffers; }
	const IndexBuffer* GetIndexBuffer() const { return m_IndexBuffer; }
private:
	std::vector<const VertexBuffer*> m_VertexBuffers;
	const IndexBuffer* m_IndexBuffer;

	uint32_t m_RendererID;
};