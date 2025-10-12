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

		if (glfwInit() == GLFW_FALSE)
		{
			std::println("Failed to initialize GLFW");
			return;
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Handle = glfwCreateWindow(m_Specification.Width, m_Specification.Height, m_Specification.Title.c_str(), nullptr, nullptr);

		if (m_Handle == nullptr)
		{
			std::println("Failed to create window");
			return;
		}

		if (m_Specification.Fullscreen)
		{
			glfwMaximizeWindow(m_Handle);
			glfwGetWindowSize(m_Handle, &m_Specification.Width, &m_Specification.Height);
		}

		glfwMakeContextCurrent(m_Handle);
		glfwShowWindow(m_Handle);

		gladLoadGL();

		m_RendererContext = RendererContext::Create(m_Specification.Width, m_Specification.Height);

		glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow* window)
			{
				Ref<WindowClosedEvent> event = CreateRef<WindowClosedEvent>();
				EventHandler::AddEvent(event);
			});

		glfwSetWindowSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height)
			{
				Ref<WindowResizedEvent> event = CreateRef<WindowResizedEvent>(width, height);
				EventHandler::AddEvent(event);
			});

		glfwSetWindowMaximizeCallback(m_Handle, [](GLFWwindow* window, int maximized)
			{

			});


		EventHandler::Subscribe(EventType::WindowSize, [&](Ref<Event> event)
			{
				Ref<WindowResizedEvent> e = std::dynamic_pointer_cast<WindowResizedEvent>(event);

				m_Specification.Width = e->Width();
				m_Specification.Height = e->Height();
			});
	}


	Window::~Window()
	{
		glfwMakeContextCurrent(nullptr);

		glfwDestroyWindow(m_Handle);
	}


	auto Window::HandleEvents() -> void
	{
		glfwPollEvents();
	}

	auto Window::Swap() -> void
	{
		glfwSwapInterval(static_cast<int32_t>(m_Specification.VSync));

		glfwSwapBuffers(m_Handle);
	}

}
