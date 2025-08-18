#include "Core/LayerStack.h"



namespace Nut
{


	LayerStack::LayerStack()
	{

	}

	LayerStack::~LayerStack()
	{
		for (auto& layer : m_Layers)
		{
			layer->OnDetach();
		}

		m_Layers.clear();
	}

	auto LayerStack::AddLayer(Ref<Nut::Layer> layer) -> void
	{
		if (std::find(m_Layers.begin(), m_Layers.end(), layer) == m_Layers.end())
		{
			m_Layers.emplace_back(layer);
		}
	}

	auto LayerStack::RemoveLayer(Ref<Nut::Layer> layer) -> void
	{
		auto location = std::find(m_Layers.begin(), m_Layers.end(), layer);

		if (location != m_Layers.end())
		{
			m_Layers.erase(location);
		}
	}

}
