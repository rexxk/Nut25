#include "Core/Application.h"

#include "Core/Input.h"
#include "Core/Timer.h"
#include "Events/EventHandler.h"
#include "UI/ImGuiContext.h"

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
	
		Input::Initialize();

		WindowSpecification windowSpec{};
		windowSpec.Width = settings.Width;
		windowSpec.Height = settings.Height;
		windowSpec.Title = "Sandbox";
		windowSpec.Fullscreen = settings.Fullscreen;
		windowSpec.VSync = settings.VSync;

		m_Window = Window::Create(windowSpec);
	
		ImGuiContext::Initialize(m_Window->Handle());

		EventHandler::Subscribe(EventType::WindowClose, [&](Ref<Event> event)
			{
				Ref<WindowClosedEvent> e = std::dynamic_pointer_cast<WindowClosedEvent>(event);
				m_IsRunning = false;
			});

	}


	auto Application::Run() -> void
	{
		std::println("Application::Run");

		m_IsRunning = true;

		Timer timer;
		Timer timestepTimer;

		uint32_t frameCount{ 0 };

		while (m_IsRunning)
		{
			double timestep = timestepTimer.ElapsedTime() / 1000.0;
			timestepTimer.Reset();

			m_Window->HandleEvents();
			EventHandler::Poll();

			ImGuiContext::BeginFrame();

			for (auto& layer : m_LayerStack)
			{
				layer->OnUpdate(timestep);
			}



			ImGuiContext::EndFrame();

			ImGuiContext::Render();


			if (timer.ElapsedTime() > 1000.0)
			{
				std::println("FPS: {}", frameCount);
				timer.Reset();

				frameCount = 0;
			}
			else
			{
				frameCount++;
			}

			m_Window->Swap();
		}


		ImGuiContext::Shutdown();
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
