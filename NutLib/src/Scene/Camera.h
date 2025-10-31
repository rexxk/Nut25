#pragma once

#include "Core/Base.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <cstdint>

namespace Nut
{

	struct CameraProperties
	{
		glm::vec3 Position{ 0.0f };
		glm::vec3 Rotation{ 0.0f };
		glm::vec3 LookAt{ 0.0f };

		float Yaw{ 0.0f };
		float Pitch{ 0.0f };

		float Distance{ 1.0f };

		float FieldOfView{ 45.0f };

		float NearPlane{ 0.1f };
		float FarPlane{ 1000.0f };
		float Aspect{ 1.0f };
	};


	struct Plane
	{
		glm::vec3 Normal{ 0.0f, 1.0f, 0.0f };
		float Distance{ 0.0f };

		Plane() = default;
		Plane(const glm::vec3& p1, const glm::vec3& normal)
			: Normal(glm::normalize(normal)), Distance(glm::dot(normal, p1))
		{

		}

		auto GetSignedDistanceToPlane(const glm::vec3& point) const -> float
		{
			return glm::dot(Normal, point) - Distance;
		}

	};

	struct Frustum
	{
		Plane TopFace{};
		Plane BottomFace{};

		Plane LeftFace{};
		Plane RightFace{};

		Plane NearFace{};
		Plane FarFace{};
	};


	class Camera
	{
	public:
		static auto Create(const glm::vec3& position, const glm::vec3& rotation, int32_t canvasWidth, int32_t canvasHeight) -> Ref<Camera>;

		Camera(const glm::vec3& position, const glm::vec3& rotation, int32_t canvasWidth, int32_t canvasHeight);

		auto ProjectionMatrix() -> glm::mat4 { return m_ProjectionMatrix; }
		auto ViewMatrix() -> glm::mat4 { return m_ViewMatrix; }

		auto Update() -> void;

		auto ViewProjectionMatrix() -> glm::mat4 { return m_ProjectionMatrix * m_ViewMatrix; }

		CameraProperties& GetProperties() { return m_Properties; }

		auto RightDirection() const -> const glm::vec3 { return glm::rotate(GetOrientation(), glm::vec3{ 1.0f, 0.0f, 0.0f }); }
		auto UpDirection() const -> const glm::vec3 { return glm::rotate(GetOrientation(), glm::vec3{ 0.0f, 1.0f, 0.0f }); }
		auto ForwardDirection() const -> const glm::vec3 { return glm::rotate(GetOrientation(), glm::vec3{ 0.0f, 0.0f, -1.0f }); }

		auto GetFrustum() -> Frustum;

	private:
		auto Resize(int32_t canvasWidth, int32_t canvasHeight) -> void;
		auto CalculateViewMatrix() -> void;

		auto CalculatePosition() -> void;
		auto GetOrientation() const -> const glm::quat { return glm::quat{ glm::vec3{-m_Properties.Pitch, -m_Properties.Yaw, 0.0f} }; }


	private:
		CameraProperties m_Properties{};


		glm::mat4 m_ProjectionMatrix{ 1.0f };
		glm::mat4 m_ViewMatrix{ 1.0f };
	};


}
