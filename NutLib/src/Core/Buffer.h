#pragma once

#include <cstdint>


namespace Nut
{


	class Buffer
	{
	public:
		Buffer(const void* data, size_t size)
		{

		}

		~Buffer()
		{
			if (m_Pointer)
			{
				delete[] m_Pointer;
				m_Pointer = nullptr;
			}
		}



		auto Data() const -> const void* { return m_Pointer; }


	private:
		unsigned char* m_Pointer{ nullptr };
		size_t m_Size{ 0 };
	};


}
