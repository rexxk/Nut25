#pragma once

#include "Core/Base.h"
#include "Core/LayerStack.h"
#include "Core/Window.h"

#include <cstdint>


namespace Nut
{


	struct ApplicationSettings
	{
		bool Fullscreen{ false };
	};


	class Application
	{
	public:
		static Ref<Window> Create(const ApplicationSettings& settings);

		Application(const ApplicationSettings& settings);


		auto Run() -> void;

		auto SetRunState(bool state) -> void { m_IsRunning = state; }

		auto AttachLayer(Ref<Nut::Layer> layer) -> void;
		auto DetachLayer(Ref<Nut::Layer> layer) -> void;


		static auto Get() -> Application& { return *s_Instance; }

	private:
		ApplicationSettings m_Settings{};

		LayerStack m_LayerStack{};

		Ref<Window> m_Window{ nullptr };

		bool m_IsRunning{ false };

		inline static Application* s_Instance{ nullptr };
	};


}
