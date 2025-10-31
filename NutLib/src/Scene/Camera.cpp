#include "Scene/Camera.h"

#include "Events/EventHandler.h"

#include <glm/gtc/matrix_transform.hpp>





namespace Nut
{


	Camera::Camera(const glm::vec3& position, const glm::vec3& rotation, int32_t canvasWidth, int32_t canvasHeight)
	{
		m_Properties.Position = position;
		m_Properties.Rotation = rotation;

		m_Properties.Distance = glm::distance(m_Properties.Position, m_Properties.LookAt);

		Resize(canvasWidth, canvasHeight);

		CalculateViewMatrix();

		EventHandler::Subscribe(EventType::WindowSize, [&](Ref<Event> event)
			{
				Ref<WindowResizedEvent> e = std::dynamic_pointer_cast<WindowResizedEvent>(event);

				Resize(e->Width(), e->Height());
			});


	}

	auto Camera::Resize(int32_t canvasWidth, int32_t canvasHeight) -> void
	{
		m_Properties.Aspect = static_cast<float>(canvasWidth) / static_cast<float>(canvasHeight);
		m_ProjectionMatrix = glm::perspective(m_Properties.FieldOfView, m_Properties.Aspect, 0.1f, 1000.0f);

	}

	auto Camera::CalculateViewMatrix() -> void
	{
		CalculatePosition();
		m_Properties.Rotation = glm::eulerAngles(GetOrientation() * (180.0f / glm::pi<float>()));

		m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Properties.Position) * glm::toMat4(GetOrientation());
		m_ViewMatrix = glm::inverse(m_ViewMatrix);
	}

	auto Camera::CalculatePosition() -> void
	{
		m_Properties.Position = m_Properties.LookAt - ForwardDirection() * m_Properties.Distance;
	}

	auto Camera::Update() -> void
	{
		CalculateViewMatrix();
	}

	auto Camera::GetFrustum() -> Frustum
	{
		Frustum frustum{};

		const float halfVerticalSide = m_Properties.FarPlane * std::tanf(glm::radians(m_Properties.FieldOfView) * 0.5f);
		const float halfHorizontalSide = halfVerticalSide * m_Properties.Aspect;
		const glm::vec3 frontMultiplicationFar = m_Properties.FarPlane * ForwardDirection();

		frustum.NearFace = { m_Properties.Position + m_Properties.NearPlane * ForwardDirection(), ForwardDirection() };
		frustum.FarFace = { m_Properties.Position + frontMultiplicationFar, -ForwardDirection() };

		frustum.RightFace = { m_Properties.Position, glm::cross(frontMultiplicationFar - RightDirection() * halfHorizontalSide, UpDirection()) };
		frustum.LeftFace = { m_Properties.Position, glm::cross(UpDirection(), frontMultiplicationFar + RightDirection() * halfHorizontalSide) };

		frustum.TopFace = { m_Properties.Position, glm::cross(RightDirection(), frontMultiplicationFar - UpDirection() * halfVerticalSide) };
		frustum.BottomFace = { m_Properties.Position, glm::cross(frontMultiplicationFar + UpDirection() * halfVerticalSide, RightDirection()) };


		return frustum;
	}


}
