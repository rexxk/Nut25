#include "Scene/CameraController.h"

#include "Core/Input.h"
#include "Events/EventHandler.h"


namespace Nut
{


	CameraController::CameraController(Ref<Camera> camera)
		: m_Camera(camera)
	{

		EventHandler::Subscribe(EventType::MouseDelta, [&](Ref<Event> event)
			{
				if (Input::IsMouseButtonPressed(MouseButton::Right))
				{
					Ref<MouseDeltaEvent> e = std::dynamic_pointer_cast<MouseDeltaEvent>(event);

					auto& cameraProperties = m_Camera->GetProperties();

					float yawSign = m_Camera->UpDirection().y < 0 ? -1.0f : 1.0f;
					cameraProperties.Yaw -= yawSign * static_cast<float>(e->X()) * m_MouseSpeed * m_Timestep;
					cameraProperties.Pitch -= static_cast<float>(e->Y()) * m_MouseSpeed * m_Timestep;
				}
			});

	}


	auto CameraController::Update(double timestep) -> void
	{
		m_Timestep = timestep;

		m_Camera->Update();
	}

}
