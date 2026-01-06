#pragma once

#include "Core/UUID.h"

#include <algorithm>
#include <ranges>

#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

namespace Nut
{


	template<typename T>
	class ComponentContainer
	{
	public:
		static auto Add(UUID uuid, const T& component) -> void
		{
			s_Components.try_emplace(uuid, std::move(component));
		}

		static auto Get(UUID uuid) -> T&
		{
			if (s_Components.contains(uuid))
			{
				return s_Components[uuid];
			}

			return *(T*)nullptr;
		}

		static auto Remove(UUID uuid) -> void
		{
			auto location = s_Components.find(uuid);

			if (location != s_Components.end())
				s_Components.erase(location);
		}

	private:
		inline static std::unordered_map<UUID, T> s_Components{};
	};

	template<typename T>
	class EntityView
	{
	public:
		static auto Add(UUID uuid) -> void
		{
			s_Entities.push_back(uuid);
		}

		static auto Remove(UUID uuid) -> void
		{
			auto location = std::find(s_Entities.begin(), s_Entities.end(), uuid);

			if (location != s_Entities.end())
				s_Entities.erase(location);
		}

		static auto Find(UUID uuid) -> bool
		{
			return (std::find(s_Entities.begin(), s_Entities.end(), uuid) != s_Entities.end());
		}

		static auto Get() -> const std::vector<UUID>&
		{
			return s_Entities;
		}

	private:
		inline static std::vector<UUID> s_Entities{};
	};

	class EntityRegistry
	{
	public:
		static auto Generate() -> UUID
		{
			UUID newUUID{};
			s_Entities.insert(newUUID);

			return newUUID;
		}

		static auto Delete(UUID& uuid) -> void
		{
			auto location = s_Entities.find(uuid);

			if (location != s_Entities.end())
				s_Entities.erase(location);
		}

	private:
		inline static std::unordered_set<UUID> s_Entities{};
	};

	class EntitySystem
	{
	public:
		template<typename T, typename ... Args>
		static auto AddComponent(UUID uuid, Args&& ... args) -> void
		{
			if (HasComponent<T>(uuid))
			{
				LOG_CORE_WARN("Entity {} already have component added", uuid);
				return;
			}

			ComponentContainer<T>::Add(uuid, T(std::forward<Args&&>(args)...));
			EntityView<T>::Add(uuid);
		}

		template<typename T>
		static auto RemoveComponent(UUID uuid) -> void
		{
			if (HasComponent<T>(uuid))
			{
				ComponentContainer<T>::Remove(uuid);
				EntityView<T>::Remove(uuid);
			}
		}

		template<typename T>
		static auto HasComponent(UUID uuid) -> bool
		{
			return EntityView<T>::Find(uuid);
		}

		template<typename T>
		static auto GetComponent(UUID uuid) -> T&
		{
			return ComponentContainer<T>::Get(uuid);
		}
	};


#if 0
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


	class Component
	{
	public:
		template<class ... T, class ... Args>
		static auto AddComponent(const UUID id, Args... args) -> void
//		static auto AddComponent(const UUID id, T&&... args) -> void
		{
			auto componentsSize = sizeof...(T);

			InsertComponent<T...>(id, std::forward_as_tuple(args...));
		}

		template<class... T, class Args>
		static auto InsertComponent(const UUID id, Args args)
		{
//			template for (auto& arg : args)
//			{
//
//			}

			for_each(args, [](auto args) {args.Print(); });
		}


		template<class Tuple, class F>
		constexpr decltype(auto) static for_each(Tuple&& tuple, F&& f)
		{
			return[]<std::size_t... I>(Tuple && tuple, F && f, std::index_sequence<I...>)
			{
				(f(std::get<I>(tuple)), ...);
				return f;
			}(std::forward<Tuple>(tuple), std::forward<F>(f), std::make_index_sequence<std::tuple_size<std::remove_reference_t<Tuple>>::value>{});
		}

//		inline static std::unordered_map<UUID, std::vector<std::variant<T...>>> ComponentMap{};
	};
#endif


}
