#pragma once


#include "Core/Base.h"
#include "Core/UUID.h"

#include "Renderer/Renderer.h"

#include <glm/glm.hpp>



namespace Nut
{


	struct EntityTransform
	{
		glm::vec3 Position{ 0.0f };
		glm::vec3 Rotation{ 0.0f };
		glm::vec3 Scale{ 1.0f };

		glm::mat4 TransformMatrix{ 1.0f };
	};

	class Mesh;

	class Entity
	{
	public:
		static auto Create(UUID meshID) -> Ref<Entity>;

		Entity(UUID meshID);

		auto CalculateTransformMatrix() -> void;
		auto CreateDebugLines(std::vector<LineVertex>& vertexList) -> void;
		auto GetTransform() -> EntityTransform& { return m_Transform; }

		auto SetEntityID(UUID uuid) -> void { m_EntityID = uuid; }
		auto EntityID() const -> const UUID { return m_EntityID; }

		auto ModelID() -> const UUID { return m_ModelID; }


	private:
		UUID m_ModelID{};

		EntityTransform m_Transform{};

		UUID m_EntityID{};
	};


}
