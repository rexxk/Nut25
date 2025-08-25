#pragma once

#include "Core/Base.h"

#include <glad/glad.h>

#include <cstdint>


namespace Nut
{


	class VertexBuffer
	{
	public:
		static auto Create() -> Ref<VertexBuffer>;

		VertexBuffer();

		auto Handle() const -> GLuint { return m_Handle; }

	private:
		GLuint m_Handle{ 0 };
	};


	class IndexBuffer
	{
	public:
		static auto Create() -> Ref<IndexBuffer>;

		IndexBuffer();

		auto Handle() const -> GLuint { return m_Handle; }

	private:
		GLuint m_Handle{ 0 };

		uint32_t m_IndexCount{ 0 };
	};

}
