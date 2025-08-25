#pragma once

#include "Core/Base.h"

#include <cstdint>
#include <memory>


namespace Nut
{


	class Buffer
	{
	public:

		inline static auto Create(const void* data, size_t size) -> Ref<Buffer>
		{
			return CreateRef<Buffer>(data, size);
		}

		Buffer(const void* data, size_t size)
		{
			SetData(data, size);
		}

		~Buffer()
		{
			Free();
		}

		auto Free() -> void
		{
			if (m_Pointer)
			{
				delete[] m_Pointer;
				m_Pointer = nullptr;
			}

			m_Size = 0;
		}

		auto Allocate(size_t size) -> void
		{
			if (m_Pointer)
				Free();

			m_Pointer = new unsigned char[size];
		}

		auto SetData(const void* data, size_t size) -> void
		{
			Allocate(size);

			std::memcpy(m_Pointer, data, size);
		}

		auto Data() const -> const void* { return m_Pointer; }

	private:
		unsigned char* m_Pointer{ nullptr };
		size_t m_Size{ 0 };
	};


}
