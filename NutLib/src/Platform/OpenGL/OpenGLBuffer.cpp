#include "Platform/OpenGL/OpenGLBuffer.h"



namespace Nut
{


	OpenGLVertexBuffer::OpenGLVertexBuffer(Ref<Buffer> buffer)
	{
		glCreateBuffers(1, &m_Handle);

		SetData(buffer);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, uint32_t size, uint32_t stride)
		: m_Stride(stride)
	{
		glCreateBuffers(1, &m_Handle);

		SetData(data, size);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		if (m_Handle)
			glDeleteBuffers(1, &m_Handle);
	}

	auto OpenGLVertexBuffer::SetData(Ref<Buffer> buffer) -> void
	{
		glNamedBufferData(m_Handle, buffer->Size(), buffer->Data(), GL_STATIC_DRAW);
	}

	auto OpenGLVertexBuffer::SetData(const void* data, uint32_t size) -> void
	{
		glNamedBufferData(m_Handle, size * m_Stride, data, GL_STATIC_DRAW);
	}

	auto OpenGLVertexBuffer::UpdateData(const void* data, uint32_t size) -> void
	{
		glNamedBufferSubData(m_Handle, 0, size, data);
	}



	OpenGLIndexBuffer::OpenGLIndexBuffer(Ref<Buffer> buffer)
		: m_IndexCount(static_cast<uint32_t>(buffer->Count()))
	{
		glCreateBuffers(1, &m_Handle);

		SetData(buffer);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(const void* data, uint32_t size)
	{
		m_IndexCount = size / sizeof(uint32_t);

		glCreateBuffers(1, &m_Handle);

		SetData(data, size);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		if (m_Handle)
			glDeleteBuffers(1, &m_Handle);
	}

	auto OpenGLIndexBuffer::SetData(Ref<Buffer> buffer) -> void
	{
		glNamedBufferData(m_Handle, buffer->Size(), buffer->Data(), GL_STATIC_DRAW);
	}

	auto OpenGLIndexBuffer::SetData(const void* data, uint32_t size) -> void
	{
		glNamedBufferData(m_Handle, size, data, GL_STATIC_DRAW);
	}



	OpenGLUniformBuffer::OpenGLUniformBuffer(Ref<Buffer> buffer)
	{
		glCreateBuffers(1, &m_Handle);

		SetData(buffer);
	}

	OpenGLUniformBuffer::OpenGLUniformBuffer(const void* data, uint32_t size)
	{
		glCreateBuffers(1, &m_Handle);

		SetData(data, size);
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		if (m_Handle != 0)
			glDeleteBuffers(1, &m_Handle);
	}

	auto OpenGLUniformBuffer::SetData(Ref<Buffer> buffer) -> void
	{
		glNamedBufferData(m_Handle, buffer->Size(), buffer->Data(), GL_STATIC_DRAW);
	}

	auto OpenGLUniformBuffer::SetData(const void* data, uint32_t size) -> void
	{
		glNamedBufferData(m_Handle, size, data, GL_STATIC_DRAW);
	}

	auto OpenGLUniformBuffer::Bind() const -> void
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_Handle);
	}

}
