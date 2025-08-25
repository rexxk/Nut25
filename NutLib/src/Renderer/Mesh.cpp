#include "Renderer/Mesh.h"



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


}
