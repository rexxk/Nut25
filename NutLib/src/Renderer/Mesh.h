#pragma once

#include "Renderer/OpenGLBuffer.h"

#include <vector>


namespace Nut
{


	class Mesh
	{
	public:
		static auto Create(const std::vector<Ref<VertexBuffer>>& vertexBuffers, Ref<IndexBuffer> indexBuffer) -> Ref<Mesh>;

		Mesh(const std::vector<Ref<VertexBuffer>>& vertexBuffers, Ref<IndexBuffer> indexBuffer);

		auto Draw() -> void;

	private:
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer{ nullptr };

	};


}
