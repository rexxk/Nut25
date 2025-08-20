#pragma once

#include "Events/Event.h"

#include "Core/Base.h"

#include <functional>
#include <unordered_map>
#include <vector>


namespace Nut
{

	class EventHandler
	{
	public:
		using EventFn = std::function<void(Ref<Event>)>;

		static auto Subscribe(EventType eventType, EventFn fn) -> void
		{
			m_Subscribers[eventType].push_back(fn);
		}

		static auto AddEvent(Ref<Event> event) -> void
		{
			m_Events.push_back(event);
		}

		static auto Invoke(const Ref<Event>& event) -> void
		{
			for (auto& fn : m_Subscribers[event->m_Type])
			{
				fn(event);
			}
		}

		static auto constexpr Poll() -> void
		{
			for (auto& event : m_Events)
			{
				Invoke(event);
			}

			m_Events.clear();
		}

	private:
		inline static std::unordered_map<EventType, std::vector<EventFn>> m_Subscribers;
		inline static std::vector<Ref<Event>> m_Events;

	};



}
