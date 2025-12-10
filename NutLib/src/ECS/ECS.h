#pragma once

#include "Core/UUID.h"

#include <algorithm>
#include <ranges>

#include <unordered_map>
#include <variant>
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



}
