#pragma once

#include "Core/Base.h"
#include "Core/Layer.h"

#include <vector>


namespace Nut
{


	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		auto AddLayer(Ref<Layer> layer) -> void;
		auto RemoveLayer(Ref<Layer> layer) -> void;

		constexpr auto begin() -> std::vector<Ref<Nut::Layer>>::iterator
		{
			return m_Layers.begin();
		}

		constexpr auto end() -> std::vector<Ref<Nut::Layer>>::iterator
		{
			return m_Layers.end();
		}

		constexpr auto cbegin() const -> const std::vector<Ref<Nut::Layer>>::const_iterator
		{
			return m_Layers.cbegin();
		}

		constexpr auto cend() const -> const std::vector<Ref<Nut::Layer>>::const_iterator
		{
			return m_Layers.cend();
		}

	private:
		std::vector<Ref<Nut::Layer>> m_Layers{};
	};


}
