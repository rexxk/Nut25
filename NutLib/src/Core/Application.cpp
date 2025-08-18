#include "Core/Application.h"

#include <print>


namespace Nut
{


	Application::Application()
	{
		std::println("Application constructor");
	}


	auto Application::Run() -> void
	{
		std::println("Application::Run");
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
