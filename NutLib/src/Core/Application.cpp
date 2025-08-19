#include "Core/Application.h"

#include <print>


namespace Nut
{


	Application::Application(const ApplicationSettings& settings)
		: m_Settings(settings)
	{
		if (s_Instance != nullptr)
		{
			std::println("Application object already exists");
			return;
		}

		s_Instance = this;

		std::println("Application constructor");

		std::println("Settings: Fullscreen - {}", m_Settings.Fullscreen);
	

		WindowSpecification windowSpec{};
		windowSpec.Width = 800;
		windowSpec.Height = 600;
		windowSpec.Title = "Sandbox";
		windowSpec.Fullscreen = settings.Fullscreen;

		m_Window = Window::Create(windowSpec);
	
	}


	auto Application::Run() -> void
	{
		std::println("Application::Run");

		SetRunState(true);

		while (m_IsRunning)
		{
			m_Window->HandleEvents();

		}
	}


	auto Application::AttachLayer(Ref<Nut::Layer> layer) -> void
	{
		m_LayerStack.AddLayer(layer);
		layer->OnAttach();
	}

	auto Application::DetachLayer(Ref<Nut::Layer> layer) -> void
	{
		m_LayerStack.RemoveLayer(layer);
	}

}
