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

		static auto ClearEntityIDs() -> void
		{
			s_Entities.clear();
		}

	private:
		inline static std::vector<UUID> s_Entities{};
	};


	template<class ... T>
	class Component
	{
	public:
//		template<class ... Args>
//		static auto AddComponent(const UUID id, Args... args) -> void
		static auto AddComponent(const UUID id, T&&... args) -> void
		{
			auto componentsSize = sizeof...(T);

			LOG_CORE_TRACE("Sizeof T... : {}", sizeof...(T));
//			LOG_CORE_TRACE("Sizeof Args... : {}", sizeof...(Args));

			for (auto i = 0; i < componentsSize; i++)
				InsertComponent<T...>(id); // , std::forward<T>(args)...);

//			InsertComponent(id, T, args...); // args);
//			auto componentType = Args...;

//			ComponentMap[id].emplace_back(T...);

			LOG_CORE_TRACE("ID: {}", id);

		}

//		template<class... T, class... Args>
		template<class... T>
//		static auto InsertComponent(const UUID id, T&&... args)
//		static auto InsertComponent(const UUID id, Args... args)
		static auto InsertComponent(const UUID id) // , T&&... args)
		{
			LOG_CORE_TRACE("InsertComponent: {} ({})", id, typeid<T...>.name());
//			ComponentMap[id].push_back(T...);
		}

//		inline static std::unordered_map<UUID, std::vector<T&&...>> ComponentMap{};
	};



}
