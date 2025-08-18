#pragma once

#include "Core/Base.h"
#include "Core/LayerStack.h"


namespace Nut
{


	class Application
	{
	public:
		Application();


		auto Run() -> void;

		auto AttachLayer(Ref<Nut::Layer> layer) -> void;
		auto DetachLayer(Ref<Nut::Layer> layer) -> void;

	private:
		LayerStack m_LayerStack{};
	};


}
