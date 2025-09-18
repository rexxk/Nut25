#include "Renderer/OpenGLBuffer.h"



namespace Nut
{


	auto VertexBuffer::Create(Ref<Buffer> buffer) -> Ref<VertexBuffer>
	{
		return CreateRef<VertexBuffer>(buffer);
	}

	VertexBuffer::VertexBuffer(Ref<Buffer> buffer)
	{
		glCreateBuffers(1, &m_Handle);

		SetData(buffer);
	}

	VertexBuffer::~VertexBuffer()
	{
		if (m_Handle)
			glDeleteBuffers(1, &m_Handle);
	}

	auto VertexBuffer::SetData(Ref<Buffer> buffer) -> void
	{
//		glNamedBufferStorage(m_Handle, buffer->Size(), buffer->Data(), GL_ARRAY_BUFFER);
//		glNamedBufferSubData(m_Handle, 0, buffer->Size(), buffer->Data());
		glNamedBufferData(m_Handle, buffer->Size(), buffer->Data(), GL_STATIC_DRAW);
	}


	auto IndexBuffer::Create(Ref<Buffer> buffer) -> Ref<IndexBuffer>
	{
		return CreateRef<IndexBuffer>(buffer);
	}

	IndexBuffer::IndexBuffer(Ref<Buffer> buffer)
		: m_IndexCount(static_cast<uint32_t>(buffer->Count()))
	{
		glCreateBuffers(1, &m_Handle);

		SetData(buffer);
	}

	IndexBuffer::~IndexBuffer()
	{
		if (m_Handle)
			glDeleteBuffers(1, &m_Handle);
	}

	auto IndexBuffer::SetData(Ref<Buffer> buffer) -> void
	{
//		glNamedBufferStorage(m_Handle, buffer->Size(), buffer->Data(), GL_ELEMENT_ARRAY_BUFFER);
//		glNamedBufferSubData(m_Handle, 0, buffer->Size(), buffer->Data());
		glNamedBufferData(m_Handle, buffer->Size(), buffer->Data(), GL_STATIC_DRAW);
	}


	auto UniformBuffer::Create(Ref<Buffer> buffer) -> Ref<UniformBuffer>
	{
		return CreateRef<UniformBuffer>(buffer);
	}

	UniformBuffer::UniformBuffer(Ref<Buffer> buffer)
	{
		glCreateBuffers(1, &m_Handle);

		SetData(buffer);
	}

	UniformBuffer::~UniformBuffer()
	{
		if (m_Handle != 0)
			glDeleteBuffers(1, &m_Handle);
	}

	auto UniformBuffer::SetData(Ref<Buffer> buffer) -> void
	{
		glNamedBufferData(m_Handle, buffer->Size(), buffer->Data(), GL_STATIC_DRAW);
	}

	auto UniformBuffer::Bind() const -> void
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_Handle);
	}

}
