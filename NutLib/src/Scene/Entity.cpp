#include "Scene/Entity.h"

#include "Renderer/Mesh.h"

#include <glm/gtc/matrix_transform.hpp>


namespace Nut
{


	auto Entity::Create(UUID modelID) -> Ref<Entity>
	{
		return CreateRef<Entity>(modelID);
	}

	Entity::Entity(UUID modelID)
		: m_ModelID(modelID)
	{

	}

	auto Entity::CalculateTransformMatrix() -> void
	{
		m_Transform.TransformMatrix = glm::mat4(1.0f) * glm::translate(glm::mat4(1.0f), m_Transform.Position);
	}

}
