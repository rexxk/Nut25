#include "Core/Window.h"

#include "Core/Application.h"
#include "Core/Base.h"
#include "Events/EventHandler.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <exception>
#include <print>


namespace Nut
{


	auto Window::Create(const WindowSpecification& spec) -> Ref<Window>
	{
		return CreateRef<Window>(spec);
	}



	Window::Window(const WindowSpecification& spec)
		: m_Specification(spec)
	{

		gladLoadGL();

		if (glfwInit() == GLFW_FALSE)
		{
			std::println("Failed to initialize GLFW");
			return;
		}

		m_Handle = glfwCreateWindow(static_cast<int>(m_Specification.Width), static_cast<int>(m_Specification.Height), m_Specification.Title.c_str(), nullptr, nullptr);

		glfwShowWindow(m_Handle);

		glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow* window)
			{
				Ref<WindowClosedEvent> event = CreateRef<WindowClosedEvent>();
				EventHandler::AddEvent(event);
			});
	}


	Window::~Window()
	{
		glfwDestroyWindow(m_Handle);
	}


	auto Window::HandleEvents() -> void
	{
		glfwPollEvents();
	}

}
