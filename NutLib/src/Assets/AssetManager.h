#pragma once

#include "Core/Base.h"
#include "Core/Log.h"
#include "Core/UUID.h"

#include <string>
#include <unordered_map>


namespace Nut
{


	template<class T>
	class AssetManager
	{
	public:
		static auto Add(const std::string& name, T&& item) -> const UUID
		{
			if (!s_Items.contains(name))
			{
				s_Items[name] = item;
				return item->ID();
			}

			LOG_CORE_WARN("Asset {} already exists", name);
			return UUID{};
		}

		static auto Get(UUID uuid) -> T
		{
			for (auto& [name, item] : s_Items)
			{
				if (item->ID() == uuid)
					return item;
			}

			return nullptr;
		}

		static auto Get(const std::string& name) -> T
		{
			if (s_Items.contains(name))
				return s_Items[name];

			return T{};
		}

		inline static std::unordered_map<std::string, T> s_Items{};
	};

}
