#pragma once

#include "Core/Base.h"

#include "Renderer/RendererContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdint>
#include <tuple>
#include <string>


namespace Nut
{


	struct WindowSpecification
	{
		int32_t Width{ 1280 };
		int32_t Height{ 720 };

		bool Fullscreen{ false };
		bool VSync{ false };

		std::string Title{ "WindowTitle" };
	};



	class Window
	{
	public:
		static auto Create(const WindowSpecification& spec) -> Ref<Window>;

		Window(const WindowSpecification& spec);
		~Window();

		auto HandleEvents() -> void;

		auto Swap() -> void;

		auto GetSize() const -> const std::pair<int32_t, int32_t> { return std::make_pair(m_Specification.Width, m_Specification.Height); }

		auto GetRendererContext() -> Ref<RendererContext> { return m_RendererContext; }
		auto Handle() -> GLFWwindow* { return m_Handle; }

	private:
		WindowSpecification m_Specification{};

		Ref<RendererContext> m_RendererContext{};

		GLFWwindow* m_Handle{ nullptr };
	};


}
