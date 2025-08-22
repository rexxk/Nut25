#pragma once


#include <print>



namespace Nut
{



	enum class EventType
	{
		None,
		WindowClose, WindowSize,
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


	class WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(int width, int height)
			: Event(), m_Width(width), m_Height(height)
		{
			m_Type = EventType::WindowSize;
		}

		virtual auto Print() -> void override
		{
			std::println("WindowResizedEvent - {}x{}", m_Width, m_Height);
		}

		auto Width() -> int { return m_Width; }
		auto Height() -> int { return m_Height; }

	private:
		int m_Width{};
		int m_Height{};
	};

}
