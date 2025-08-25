#include "Renderer/OpenGLBuffer.h"



namespace Nut
{


	auto VertexBuffer::Create() -> Ref<VertexBuffer>
	{
		return CreateRef<VertexBuffer>();
	}

	VertexBuffer::VertexBuffer()
	{
		glCreateBuffers(1, &m_Handle);
	}


	auto IndexBuffer::Create() -> Ref<IndexBuffer>
	{
		return CreateRef<IndexBuffer>();
	}

	IndexBuffer::IndexBuffer()
	{
		glCreateBuffers(1, &m_Handle);
	}


}
