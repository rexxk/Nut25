#pragma once

#include "Core/Base.h"
#include "Core/UUID.h"

#include <unordered_map>


namespace Nut
{


	class Mesh;
	class Model;

	template<class T>
	class AssetManager
	{
	public:
		static auto Add(T item) -> const UUID
		{
			if (!s_Items.contains(item->ID()))
			{
				s_Items[item->ID()] = item;
			}

			return item->ID();
		}

		static auto Get(UUID uuid) -> T
		{
			if (s_Items.contains(uuid))
				return s_Items[uuid];

			return nullptr;
		}

		inline static std::unordered_map<UUID, T> s_Items{};
	};

}
