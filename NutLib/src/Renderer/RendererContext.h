#pragma once

#include "Core/Base.h"

#include <cstdint>


namespace Nut
{


	enum class RendererAPI
	{
		None = 0,
		OpenGL,
		Vulkan,
	};


	class RendererContext
	{
	public:
		static Ref<RendererContext> Create(RendererAPI api, int32_t windowWidth, int32_t windowHeight);

		RendererContext(int32_t windowWidth, int32_t windowHeight);

		auto BeginScene() -> void;


		static auto API() -> const RendererAPI { return s_RendererAPI; }

	private:
		inline static RendererAPI s_RendererAPI{ RendererAPI::None };
	};


}
