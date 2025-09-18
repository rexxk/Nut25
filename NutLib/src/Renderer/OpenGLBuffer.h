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

		VertexBuffer(Ref<Buffer> buffer);
		~VertexBuffer();

		auto SetData(Ref<Buffer> buffer) -> void;

		auto Handle() const -> GLuint { return m_Handle; }

	private:
		GLuint m_Handle{ 0 };
	};


	class IndexBuffer
	{
	public:
		static auto Create(Ref<Buffer> buffer) -> Ref<IndexBuffer>;

		IndexBuffer(Ref<Buffer> buffer);
		~IndexBuffer();

		auto SetData(Ref<Buffer> buffer) -> void;

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
