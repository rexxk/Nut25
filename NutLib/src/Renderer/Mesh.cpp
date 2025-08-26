#include "Renderer/Mesh.h"

#include <glad/glad.h>



namespace Nut
{


	auto Mesh::Create(const std::vector<Ref<VertexBuffer>>& vertexBuffers, Ref<IndexBuffer> indexBuffer) -> Ref<Mesh>
	{
		return CreateRef<Mesh>(vertexBuffers, indexBuffer);
	}


	Mesh::Mesh(const std::vector<Ref<VertexBuffer>>& vertexBuffers, Ref<IndexBuffer> indexBuffer)
		: m_VertexBuffers(vertexBuffers), m_IndexBuffer(indexBuffer)
	{

	}


	auto Mesh::Draw() -> void
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffers[0]->Handle());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer->Handle());

		glDrawElements(GL_TRIANGLES, m_IndexBuffer->IndexCount(), GL_UNSIGNED_INT, nullptr);
	}


}
