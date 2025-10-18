#pragma once


#include "Core/Defines.h"


#include <cstdint>
#include <print>



namespace Nut
{



	enum class EventType
	{
		None,
		WindowClose, WindowSize,
		MouseMove, MouseButtonPress, MouseButtonRelease, MouseScroll, MouseDelta,
		KeyPress, KeyRelease, KeyType,
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


	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(int32_t x, int32_t y)
			: Event(), m_X(x), m_Y(y)
		{
			m_Type = EventType::MouseMove;
		}

		virtual auto Print() -> void override
		{
			std::println("MouseMovedEvent - {}x{}", m_X, m_Y);
		}

		auto X() const -> int32_t { return m_X; }
		auto Y() const -> int32_t { return m_Y; }

	private:
		int32_t m_X{ 0 };
		int32_t m_Y{ 0 };
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(int32_t y)
			: Event(), m_Y(y)
		{
			m_Type = EventType::MouseScroll;
		}

		auto Y() const -> int32_t { return m_Y; }

	private:
		int32_t m_Y{ 0 };
	};

	class MouseDeltaEvent : public Event
	{
	public:
		MouseDeltaEvent(int32_t x, int32_t y, int32_t z = 0)
			: Event(), m_X(x), m_Y(y), m_Z(z)
		{
			m_Type = EventType::MouseDelta;
		}

		auto X() const -> int32_t { return m_X; }
		auto Y() const -> int32_t { return m_Y; }
		auto Z() const -> int32_t { return m_Z; }

	private:
		int32_t m_X{ 0 };
		int32_t m_Y{ 0 };
		int32_t m_Z{ 0 };
	};

	class MouseButtonPressedEvent : public Event
	{
	public:
		MouseButtonPressedEvent(MouseButton button)
			: Event(), m_Button(button)
		{
			m_Type = EventType::MouseButtonPress;
		}

		auto Button() const -> MouseButton { return m_Button; }

	private:
		MouseButton m_Button;
	};


	class MouseButtonReleasedEvent : public Event
	{
	public:
		MouseButtonReleasedEvent(MouseButton button)
			: Event(), m_Button(button)
		{
			m_Type = EventType::MouseButtonRelease;
		}

		auto Button() const -> MouseButton { return m_Button; }

	private:
		MouseButton m_Button;
	};

	class KeyPressedEvent : public Event
	{
	public:
		KeyPressedEvent(uint16_t key)
			: Event(), m_Key(key)
		{
			m_Type = EventType::KeyPress;
		}

		auto Key() const -> uint16_t { return m_Key; }

	private:
		uint16_t m_Key;
	};

	class KeyReleasedEvent : public Event
	{
	public:
		KeyReleasedEvent(uint16_t key)
			: Event(), m_Key(key)
		{
			m_Type = EventType::KeyRelease;
		}

		auto Key() const -> uint16_t { return m_Key; }

	private:
		uint16_t m_Key;
	};

	class KeyTypedEvent : public Event
	{
	public:
		KeyTypedEvent(uint16_t key)
			: Event(), m_Key(key)
		{
			m_Type = EventType::KeyType;
		}

		auto Key() const -> uint16_t { return m_Key; }

	private:
		uint16_t m_Key;
	};


}
