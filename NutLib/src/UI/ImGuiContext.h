#pragma once


#include <GLFW/glfw3.h>


namespace Nut
{

	class ImGuiContext
	{
	public:
		static auto Initialize(GLFWwindow* window) -> void;
		static auto Shutdown() -> void;

		static auto BeginFrame() -> void;
		static auto EndFrame() -> void;

		static auto Render() -> void;
	};

}
