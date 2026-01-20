#pragma once

#include "Core/Buffer.h"


namespace Nut
{

	enum class ImageCompression
	{
		Raw,
		PNG,
		JPG,
	};

	class Image
	{
	public:
		Image() = default;

	private:
		Buffer m_DataBuffer{};
	};


}
