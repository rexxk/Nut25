#include "Core/Application.h"

#include "Core/Exception.h"
#include "Core/Input.h"
#include "Core/Log.h"
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
			LOG_CORE_WARN("Application object already exists");
			return;
		}

		s_Instance = this;

		LOG_CORE_TRACE("Application constructor");

		LOG_CORE_TRACE("Settings: Fullscreen - {}", m_Settings.Fullscreen);
	
		Input::Initialize();

		WindowSpecification windowSpec{};
		windowSpec.Width = settings.Width;
		windowSpec.Height = settings.Height;
		windowSpec.Title = "Sandbox";
		windowSpec.Fullscreen = settings.Fullscreen;
		windowSpec.VSync = settings.VSync;

		try
		{
			m_Window = Window::Create(windowSpec);
	
			ImGuiContext::Initialize(m_Window->Handle());

		}
		catch (Exception& ex)
		{
			LOG_CORE_ERROR("Application error: {}", ex.what());

			throw Exception("Error in application constructor"sv);
		}

		EventHandler::Subscribe(EventType::WindowClose, [&](Ref<Event> event)
			{
				Ref<WindowClosedEvent> e = std::dynamic_pointer_cast<WindowClosedEvent>(event);
				m_IsRunning = false;
			});

	}


	auto Application::Run() -> void
	{
		LOG_CORE_TRACE("Application::Run");

		m_IsRunning = true;

		Timer timer;
		Timer timestepTimer;

		uint32_t frameCount{ 0 };

		while (m_IsRunning)
		{
			double timestep = timestepTimer.ElapsedTime() / 1000.0;
			timestepTimer.Reset();

			Input::Update();

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
				LOG_CORE_TRACE("FPS: {}", frameCount);
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
