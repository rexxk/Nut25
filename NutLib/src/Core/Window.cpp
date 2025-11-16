#include "Core/Window.h"

#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Defines.h"
#include "Core/Exception.h"
#include "Core/Log.h"
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


	auto IntToMouseButton(int button) -> MouseButton
	{
		switch (button)
		{
			case 0: return MouseButton::Left;
			case 1: return MouseButton::Right;
			case 2: return MouseButton::Middle;
		}

		return MouseButton::Left;
	}


	Window::Window(const WindowSpecification& spec)
		: m_Specification(spec)
	{
		try
		{
			if (glfwInit() == GLFW_FALSE)
			{
				throw Exception("Failed to initialize GLFW"sv);
			}
	
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
			glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			m_Handle = glfwCreateWindow(m_Specification.Width, m_Specification.Height, m_Specification.Title.c_str(), nullptr, nullptr);

			if (m_Handle == nullptr)
			{
				throw Exception("Failed to create window"sv);
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

			glfwSetCursorPosCallback(m_Handle, [](GLFWwindow* window, double xPosition, double yPosition)
				{
					Ref<MouseMovedEvent> event = CreateRef<MouseMovedEvent>(static_cast<int32_t>(xPosition), static_cast<int32_t>(yPosition));
					EventHandler::AddEvent(event);
				});

			glfwSetMouseButtonCallback(m_Handle, [](GLFWwindow* window, int button, int action, int mods)
				{
					if (action == GLFW_PRESS)
					{
						Ref<MouseButtonPressedEvent> event = CreateRef<MouseButtonPressedEvent>(IntToMouseButton(button));
						EventHandler::AddEvent(event);
					}
					else if (action == GLFW_RELEASE)
					{
						Ref<MouseButtonReleasedEvent> event = CreateRef<MouseButtonReleasedEvent>(IntToMouseButton(button));
						EventHandler::AddEvent(event);
					}

				});

			glfwSetScrollCallback(m_Handle, [](GLFWwindow* window, double xOffset, double yOffset)
				{
					Ref<MouseScrolledEvent> event = CreateRef<MouseScrolledEvent>(static_cast<int32_t>(yOffset));
					EventHandler::AddEvent(event);
				});

			glfwSetKeyCallback(m_Handle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
				{
					if (action == GLFW_PRESS)
					{
						Ref<KeyPressedEvent> event = CreateRef<KeyPressedEvent>(static_cast<uint16_t>(key));
						EventHandler::AddEvent(event);
					}
					else if (action == GLFW_RELEASE)
					{
						Ref<KeyReleasedEvent> event = CreateRef<KeyReleasedEvent>(static_cast<uint16_t>(key));
						EventHandler::AddEvent(event);
					}
				});

			glfwSetCharCallback(m_Handle, [](GLFWwindow* window, unsigned int codepoint)
				{
					Ref<KeyTypedEvent> event = CreateRef<KeyTypedEvent>(static_cast<uint16_t>(codepoint));
					EventHandler::AddEvent(event);
				});


			EventHandler::Subscribe(EventType::WindowSize, [&](Ref<Event> event)
				{
					Ref<WindowResizedEvent> e = std::dynamic_pointer_cast<WindowResizedEvent>(event);

					m_Specification.Width = e->Width();
					m_Specification.Height = e->Height();
				});

		}
		catch (Exception ex)
		{
			std::string_view message = ex.what();
			LOG_CORE_ERROR("Window exception: {}", message);
			__debugbreak();
		}
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
