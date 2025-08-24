#pragma once

#include "Core/Base.h"

#include <cstdint>


namespace Nut
{


	class RendererContext
	{
	public:
		static Ref<RendererContext> Create(int32_t windowWidth, int32_t windowHeight);

		RendererContext(int32_t windowWidth, int32_t windowHeight);

		auto BeginScene() -> void;
	};


}
