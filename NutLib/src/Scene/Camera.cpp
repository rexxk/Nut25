#include "Scene/Camera.h"

#include "Events/EventHandler.h"

#include <glm/gtc/matrix_transform.hpp>





namespace Nut
{

	auto Frustum::IsOnFrustum(const AABB& aabb, const glm::mat4& transform) -> bool
	{
		const glm::vec3 globalCenter{ transform * glm::vec4(aabb.Center, 1.0f) };

		return (IsOnOrForwardPlane(aabb, LeftFace) && IsOnOrForwardPlane(aabb, RightFace) &&
			IsOnOrForwardPlane(aabb, TopFace) && IsOnOrForwardPlane(aabb, BottomFace) &&
			IsOnOrForwardPlane(aabb, NearFace) && IsOnOrForwardPlane(aabb, FarFace));
	}

	auto Frustum::IsOnOrForwardPlane(const AABB& aabb, const Plane& plane) const -> bool
	{
		const float r = aabb.Extents.x * std::abs(plane.Normal.x) + aabb.Extents.y * std::abs(plane.Normal.y) + aabb.Extents.z * std::abs(plane.Normal.z);

		return -r <= plane.GetSignedDistanceToPlane(aabb.Center);
	}



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
		UpdateFOV();
//		m_ProjectionMatrix = glm::perspective(glm::radians(m_Properties.FieldOfView), m_Properties.Aspect, m_Properties.NearPlane, m_Properties.FarPlane);

	}

	auto Camera::UpdateFOV() -> void
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(m_Properties.FieldOfView), m_Properties.Aspect, m_Properties.NearPlane, m_Properties.FarPlane);
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


		glm::vec3 farCenter = m_Properties.Position + ForwardDirection() * m_Properties.FarPlane;
		glm::vec3 nearCenter = m_Properties.Position + ForwardDirection() * m_Properties.NearPlane;

		auto fov = glm::radians(m_Properties.FieldOfView) / 2.0f;
		auto nearHeight = 2.0f * std::tanf(fov) * m_Properties.NearPlane;
		auto farHeight = 2.0f * std::tanf(fov) * m_Properties.FarPlane;
		auto nearWidth = nearHeight * m_Properties.Aspect;
		auto farWidth = farHeight * m_Properties.Aspect;

		m_FrustumPoints.FarTopLeft = farCenter + (UpDirection() * (farHeight * 0.5f)) - RightDirection() * (farWidth * 0.5f);
		m_FrustumPoints.FarTopRight = farCenter + (UpDirection() * (farHeight * 0.5f)) + RightDirection() * (farWidth * 0.5f);
		m_FrustumPoints.FarBottomLeft = farCenter - (UpDirection() * (farHeight * 0.5f)) - RightDirection() * (farWidth * 0.5f);
		m_FrustumPoints.FarBottomRight = farCenter - (UpDirection() * (farHeight * 0.5f)) + RightDirection() * (farWidth * 0.5f);

		m_FrustumPoints.NearTopLeft = nearCenter + (UpDirection() * (nearHeight * 0.5f)) - RightDirection() * (nearWidth * 0.5f);
		m_FrustumPoints.NearTopRight = nearCenter + (UpDirection() * (nearHeight * 0.5f)) + RightDirection() * (nearWidth * 0.5f);
		m_FrustumPoints.NearBottomLeft = nearCenter - (UpDirection() * (nearHeight * 0.5f)) - RightDirection() * (nearWidth * 0.5f);
		m_FrustumPoints.NearBottomRight = nearCenter - (UpDirection() * (nearHeight * 0.5f)) + RightDirection() * (nearWidth * 0.5f);

		return frustum;
	}

	auto Camera::CreateFrustumLines(std::vector<LineVertex>& vertexList) -> void
	{
		{
			LineVertex vertex{};
			vertex.Color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);

			// Near square
			vertex.Position = m_FrustumPoints.NearBottomLeft;
			vertexList.push_back(vertex);
			vertex.Position = m_FrustumPoints.NearBottomRight;
			vertexList.push_back(vertex);

			vertex.Position = m_FrustumPoints.NearBottomRight;
			vertexList.push_back(vertex);
			vertex.Position = m_FrustumPoints.NearTopRight;
			vertexList.push_back(vertex);

			vertex.Position = m_FrustumPoints.NearTopRight;
			vertexList.push_back(vertex);
			vertex.Position = m_FrustumPoints.NearTopLeft;
			vertexList.push_back(vertex);

			vertex.Position = m_FrustumPoints.NearTopLeft;
			vertexList.push_back(vertex);
			vertex.Position = m_FrustumPoints.NearBottomLeft;
			vertexList.push_back(vertex);

			// Far square
			vertex.Position = m_FrustumPoints.FarBottomLeft;
			vertexList.push_back(vertex);
			vertex.Position = m_FrustumPoints.FarBottomRight;
			vertexList.push_back(vertex);

			vertex.Position = m_FrustumPoints.FarBottomRight;
			vertexList.push_back(vertex);
			vertex.Position = m_FrustumPoints.FarTopRight;
			vertexList.push_back(vertex);

			vertex.Position = m_FrustumPoints.FarTopRight;
			vertexList.push_back(vertex);
			vertex.Position = m_FrustumPoints.FarTopLeft;
			vertexList.push_back(vertex);

			vertex.Position = m_FrustumPoints.FarTopLeft;
			vertexList.push_back(vertex);
			vertex.Position = m_FrustumPoints.FarBottomLeft;
			vertexList.push_back(vertex);

			// Near-far connections
			vertex.Position = m_FrustumPoints.NearBottomLeft;
			vertexList.push_back(vertex);
			vertex.Position = m_FrustumPoints.FarBottomLeft;
			vertexList.push_back(vertex);

			vertex.Position = m_FrustumPoints.NearBottomRight;
			vertexList.push_back(vertex);
			vertex.Position = m_FrustumPoints.FarBottomRight;
			vertexList.push_back(vertex);

			vertex.Position = m_FrustumPoints.NearTopLeft;
			vertexList.push_back(vertex);
			vertex.Position = m_FrustumPoints.FarTopLeft;
			vertexList.push_back(vertex);

			vertex.Position = m_FrustumPoints.NearTopRight;
			vertexList.push_back(vertex);
			vertex.Position = m_FrustumPoints.FarTopRight;
			vertexList.push_back(vertex);
		}

	}

}
