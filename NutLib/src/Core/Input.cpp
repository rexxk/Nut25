#include "Core/Input.h"

#include "Core/Log.h"
#include "Events/EventHandler.h"


#include <vector>
#include <unordered_map>


namespace Nut
{


	struct RawInputData
	{
		std::vector<bool> MouseButtonStatus;
		std::vector<bool> KeyStatus;

		int32_t LastMouseXPosition{ -1 };
		int32_t LastMouseYPosition{ -1 };
	
		int32_t DeltaX{ 0 };
		int32_t DeltaY{ 0 };
		int32_t DeltaZ{ 0 };
	};

	static RawInputData s_RawInputData;




	auto Input::Initialize() -> void
	{
		s_RawInputData.MouseButtonStatus.resize(static_cast<size_t>(MouseButton::ButtonCount), false);
		s_RawInputData.KeyStatus.resize(256, false);

		EventHandler::Subscribe(EventType::MouseButtonPress, [](Ref<Event> event)
			{
				Ref<MouseButtonPressedEvent> e = std::dynamic_pointer_cast<MouseButtonPressedEvent>(event);

				s_RawInputData.MouseButtonStatus[static_cast<size_t>(e->Button())] = true;
			});

		EventHandler::Subscribe(EventType::MouseButtonRelease, [](Ref<Event> event)
			{
				Ref<MouseButtonReleasedEvent> e = std::dynamic_pointer_cast<MouseButtonReleasedEvent>(event);

				s_RawInputData.MouseButtonStatus[static_cast<size_t>(e->Button())] = false;
			});

		EventHandler::Subscribe(EventType::KeyPress, [](Ref<Event> event)
			{
				Ref<KeyPressedEvent> e = std::dynamic_pointer_cast<KeyPressedEvent>(event);

				if (e->Key() < 256)
					s_RawInputData.KeyStatus[static_cast<size_t>(e->Key())] = true;
			});

		EventHandler::Subscribe(EventType::KeyRelease, [](Ref<Event> event)
			{
				Ref<KeyReleasedEvent> e = std::dynamic_pointer_cast<KeyReleasedEvent>(event);

				if (e->Key() < 256)
					s_RawInputData.KeyStatus[static_cast<size_t>(e->Key())] = false;
			});

		EventHandler::Subscribe(EventType::MouseMove, [](Ref<Event> event)
			{
				Ref<MouseMovedEvent> e = std::dynamic_pointer_cast<MouseMovedEvent>(event);

				if (s_RawInputData.LastMouseXPosition == -1 || s_RawInputData.LastMouseYPosition == -1)
				{
					s_RawInputData.LastMouseXPosition = e->X();
					s_RawInputData.LastMouseYPosition = e->Y();

					return;
				}

				s_RawInputData.DeltaX = s_RawInputData.LastMouseXPosition - e->X();
				s_RawInputData.DeltaY = s_RawInputData.LastMouseYPosition - e->Y();

				s_RawInputData.LastMouseXPosition = e->X();
				s_RawInputData.LastMouseYPosition = e->Y();
			});

		EventHandler::Subscribe(EventType::MouseScroll, [](Ref<Event> event)
			{
				Ref<MouseScrolledEvent> e = std::dynamic_pointer_cast<MouseScrolledEvent>(event);
				s_RawInputData.DeltaZ = e->Y();
			});
	}


	auto Input::IsMouseButtonPressed(MouseButton button) -> bool
	{
		return s_RawInputData.MouseButtonStatus[static_cast<size_t>(button)];
	}

	auto Input::IsKeyPressed(Keys key) -> bool
	{
		if (std::underlying_type<Keys>::type(key) < 256)
			return s_RawInputData.KeyStatus[std::underlying_type<Keys>::type(key)];

		return false;
	}

	auto Input::Update() -> void
	{
		if (s_RawInputData.DeltaX != 0 || s_RawInputData.DeltaY != 0 || s_RawInputData.DeltaZ != 0)
		{
			Ref<MouseDeltaEvent> event = CreateRef<MouseDeltaEvent>(s_RawInputData.DeltaX, s_RawInputData.DeltaY, s_RawInputData.DeltaZ);
			EventHandler::AddEvent(event);

			s_RawInputData.DeltaX = 0;
			s_RawInputData.DeltaY = 0;
			s_RawInputData.DeltaZ = 0;
		}
	}

}
