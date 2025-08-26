#pragma once

#include "Core/Base.h"
#include "Core/LayerStack.h"
#include "Core/Window.h"

#include <cstdint>


namespace Nut
{


	struct ApplicationSettings
	{
		int Width{ 800 };
		int Height{ 600 };

		bool VSync{ false };
		bool Fullscreen{ false };
	};


	class Application
	{
	public:
		Application(const ApplicationSettings& settings);

		auto Run() -> void;

		auto AttachLayer(Ref<Nut::Layer> layer) -> void;
		auto DetachLayer(Ref<Nut::Layer> layer) -> void;

		auto GetWindow() -> Ref<Window> { return m_Window; }
		static auto Get() -> Application& { return *s_Instance; }

	private:
		ApplicationSettings m_Settings{};

		LayerStack m_LayerStack{};

		Ref<Window> m_Window{ nullptr };

		bool m_IsRunning{ false };

		inline static Application* s_Instance{ nullptr };
	};


}
