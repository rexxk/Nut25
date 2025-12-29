#pragma once

#include "Renderer/Buffer.h"

#include "Core/Base.h"
#include "Core/Buffer.h"

#include <glad/glad.h>

#include <cstdint>


namespace Nut
{


	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:

		OpenGLVertexBuffer(Ref<Buffer> buffer);
		OpenGLVertexBuffer(const void* data, uint32_t size, uint32_t stride);
		virtual ~OpenGLVertexBuffer();

		virtual auto SetData(Ref<Buffer> buffer) -> void override;
		virtual auto SetData(const void* data, uint32_t size) -> void override;
		virtual auto UpdateData(const void* data, uint32_t size) -> void override;

		virtual auto Handle() const -> uint32_t override { return m_Handle; }

		virtual auto Stride() const -> const uint32_t override { return m_Stride; }

	private:
		GLuint m_Handle{ 0l };
		uint32_t m_Stride{ 0l };
	};


	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		static auto Create(Ref<Buffer> buffer) -> Ref<IndexBuffer>;
		static auto Create(const void* data, uint32_t size) -> Ref<IndexBuffer>;

		OpenGLIndexBuffer(Ref<Buffer> buffer);
		OpenGLIndexBuffer(const void* data, uint32_t size);
		virtual ~OpenGLIndexBuffer();

		virtual auto SetData(Ref<Buffer> buffer) -> void override;
		virtual auto SetData(const void* data, uint32_t size) -> void override;

		virtual auto IndexCount() const -> uint32_t override { return m_IndexCount; }

		virtual auto Handle() const -> GLuint override { return m_Handle; }

	private:
		GLuint m_Handle{ 0 };

		uint32_t m_IndexCount{ 0 };
	};


	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(Ref<Buffer> buffer);
		OpenGLUniformBuffer(const void* data, uint32_t size);
		virtual ~OpenGLUniformBuffer();

		virtual auto SetData(Ref<Buffer> buffer) -> void override;
		virtual auto SetData(const void* data, uint32_t size) -> void override;

		virtual auto Bind() const -> void override;

		virtual auto Handle() const -> const GLuint override { return m_Handle; }

	private:
		GLuint m_Handle{ 0 };
	};
}
