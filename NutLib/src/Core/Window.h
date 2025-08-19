#pragma once

#include "Core/Base.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdint>
#include <string>


namespace Nut
{


	struct WindowSpecification
	{
		uint32_t Width{ 1280 };
		uint32_t Height{ 720 };

		bool Fullscreen{ false };
		bool VSync{ false };

		std::string Title{ "WindowTitle" };
	};



	class Window
	{
	public:
		static Ref<Window> Create(const WindowSpecification& spec);

		Window(const WindowSpecification& spec);
		~Window();

	private:
		WindowSpecification m_Specification{};

		GLFWwindow* m_Handle{ nullptr };
	};


}
