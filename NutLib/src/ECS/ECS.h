#pragma once

#include "Core/UUID.h"

#include <ranges>

#include <unordered_map>
#include <vector>


namespace Nut
{

	class ECS
	{
	public:
		static auto GetEntityID() -> const UUID
		{
			UUID id{};
			s_Entities.push_back(id);
			return id;
		}

		static auto AddEntityID(const UUID id) -> void
		{
			if (std::ranges::find(s_Entities, id) == s_Entities.end())
				s_Entities.push_back(id);
		}

	private:
		inline static std::vector<UUID> s_Entities{};
	};


}
