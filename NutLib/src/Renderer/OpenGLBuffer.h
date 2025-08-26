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

}
