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

		auto AttachLayer(Ref<Nut::Layer> layer) -> void;
		auto DetachLayer(Ref<Nut::Layer> layer) -> void;

	private:
		ApplicationSettings m_Settings{};

		LayerStack m_LayerStack{};

		Ref<Window> m_Window{ nullptr };
	};


}
