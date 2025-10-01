#pragma once

#include "Core/Base.h"
#include "Core/Buffer.h"

#include <glad/glad.h>

#include <cstdint>


namespace Nut
{


	class VertexBuffer
	{
	public:
		static auto Create(Ref<Buffer> buffer) -> Ref<VertexBuffer>;
		static auto Create(const void* data, uint32_t size, uint32_t stride) -> Ref<VertexBuffer>;

		VertexBuffer(Ref<Buffer> buffer);
		VertexBuffer(const void* data, uint32_t size, uint32_t stride);
		~VertexBuffer();

		auto SetData(Ref<Buffer> buffer) -> void;
		auto SetData(const void* data, uint32_t size) -> void;
		auto UpdateData(const void* data, uint32_t size) -> void;

		auto Handle() const -> GLuint { return m_Handle; }

		auto Stride() const -> const uint32_t { return m_Stride; }

	private:
		GLuint m_Handle{ 0l };

		uint32_t m_Stride{ 0l };
	};


	class IndexBuffer
	{
	public:
		static auto Create(Ref<Buffer> buffer) -> Ref<IndexBuffer>;
		static auto Create(const void* data, uint32_t size) -> Ref<IndexBuffer>;

		IndexBuffer(Ref<Buffer> buffer);
		IndexBuffer(const void* data, uint32_t size);
		~IndexBuffer();

		auto SetData(Ref<Buffer> buffer) -> void;
		auto SetData(const void* data, uint32_t size) -> void;

		auto IndexCount() const -> uint32_t { return m_IndexCount; }

		auto Handle() const -> GLuint { return m_Handle; }

	private:
		GLuint m_Handle{ 0 };

		uint32_t m_IndexCount{ 0 };
	};


	class UniformBuffer
	{
	public:
		static auto Create(Ref<Buffer> buffer) -> Ref<UniformBuffer>;
		static auto Create(const void* data, uint32_t size) -> Ref<UniformBuffer>;

		UniformBuffer(Ref<Buffer> buffer);
		UniformBuffer(const void* data, uint32_t size);
		~UniformBuffer();

		auto SetData(Ref<Buffer> buffer) -> void;
		auto SetData(const void* data, uint32_t size) -> void;

		auto Bind() const -> void;

		auto Handle() const -> const GLuint { return m_Handle; }

	private:
		GLuint m_Handle{ 0 };
	};
}
