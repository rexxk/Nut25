#include "Scene/CameraController.h"

#include "Core/Defines.h"
#include "Core/Input.h"
#include "Core/Log.h"
#include "Events/EventHandler.h"


namespace Nut
{


	CameraController::CameraController(Ref<Camera> camera)
		: m_Camera(camera)
	{

		EventHandler::Subscribe(EventType::MouseDelta, [&](Ref<Event> event)
			{
				Ref<MouseDeltaEvent> e = std::dynamic_pointer_cast<MouseDeltaEvent>(event);
				auto& cameraProperties = m_Camera->GetProperties();

				if (Input::IsMouseButtonPressed(MouseButton::Right))
				{
					float yawSign = m_Camera->UpDirection().y < 0 ? -1.0f : 1.0f;
					cameraProperties.Yaw -= yawSign * static_cast<float>(e->X()) * m_MouseSpeed * static_cast<float>(m_Timestep);
					cameraProperties.Pitch -= static_cast<float>(e->Y()) * m_MouseSpeed * static_cast<float>(m_Timestep);

					return;
				}

				if (Input::IsMouseButtonPressed(MouseButton::Middle))
				{
					cameraProperties.LookAt -= m_Camera->RightDirection() * m_MouseSpeed * static_cast<float>(e->X());
					cameraProperties.LookAt += m_Camera->UpDirection() * m_MouseSpeed * static_cast<float>(e->Y());

					return;
				}

			});

	}


	auto CameraController::Update(double timestep) -> void
	{
		m_Timestep = timestep;

		m_Camera->Update();

		auto& cameraProperties = m_Camera->GetProperties();

		if (Input::IsKeyPressed(Keys::W))
		{
			cameraProperties.LookAt += m_Camera->ForwardDirection() * m_WalkSpeed;
		}
		if (Input::IsKeyPressed(Keys::A))
		{
			cameraProperties.LookAt -= m_Camera->RightDirection() * m_WalkSpeed;
		}
		if (Input::IsKeyPressed(Keys::S))
		{
			cameraProperties.LookAt -= m_Camera->ForwardDirection() * m_WalkSpeed;
		}
		if (Input::IsKeyPressed(Keys::D))
		{
			cameraProperties.LookAt += m_Camera->RightDirection() * m_WalkSpeed;
		}

	}

}
