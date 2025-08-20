#pragma once


#include <print>



namespace Nut
{



	enum class EventType
	{
		None,
		WindowClose,
	};



	class Event
	{
	public:
		Event()
			: m_Type(EventType::None)
		{

		}

		virtual ~Event() {}

		virtual auto Print() -> void
		{
			std::println("Event base class");
		}

		EventType m_Type{ EventType::None };
	};


	class WindowClosedEvent : public Event
	{
	public:
		WindowClosedEvent()
			: Event()
		{
			m_Type = EventType::WindowClose;
		}

		virtual auto Print() -> void override
		{
			std::println("WindowClosedEvent");
		}

	};


}
