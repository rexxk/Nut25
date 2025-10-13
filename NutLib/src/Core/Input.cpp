#include "Core/Input.h"

#include "Events/EventHandler.h"


#include <vector>
#include <unordered_map>


namespace Nut
{

	static std::vector<bool> s_MouseButtonStatus;

	static std::vector<bool> s_KeyStatus;


	auto Input::Initialize() -> void
	{
		s_MouseButtonStatus.resize(static_cast<size_t>(MouseButton::ButtonCount), false);
		s_KeyStatus.resize(256, false);

		EventHandler::Subscribe(EventType::MouseButtonPress, [](Ref<Event> event)
			{
				Ref<MouseButtonPressedEvent> e = std::dynamic_pointer_cast<MouseButtonPressedEvent>(event);

				s_MouseButtonStatus[static_cast<size_t>(e->Button())] = true;
			});

		EventHandler::Subscribe(EventType::MouseButtonRelease, [](Ref<Event> event)
			{
				Ref<MouseButtonReleasedEvent> e = std::dynamic_pointer_cast<MouseButtonReleasedEvent>(event);

				s_MouseButtonStatus[static_cast<size_t>(e->Button())] = false;
			});

		EventHandler::Subscribe(EventType::KeyPress, [](Ref<Event> event)
			{
				Ref<KeyPressedEvent> e = std::dynamic_pointer_cast<KeyPressedEvent>(event);

				if (e->Key() < 256)
					s_KeyStatus[static_cast<size_t>(e->Key())] = true;
			});

		EventHandler::Subscribe(EventType::KeyRelease, [](Ref<Event> event)
			{
				Ref<KeyReleasedEvent> e = std::dynamic_pointer_cast<KeyReleasedEvent>(event);

				if (e->Key() < 256)
					s_KeyStatus[static_cast<size_t>(e->Key())] = false;
			});
	}


	auto Input::IsMouseButtonPressed(MouseButton button) -> bool
	{
		return s_MouseButtonStatus[static_cast<size_t>(button)];
	}

	auto Input::IsKeyPressed(uint16_t key) -> bool
	{
		if (key < 256)
			return s_KeyStatus[key];

		return false;
	}

}
