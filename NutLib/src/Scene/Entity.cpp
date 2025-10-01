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
		m_Transform.TransformMatrix = glm::mat4(1.0f) * glm::translate(glm::mat4(1.0f), m_Transform.Position)
			* glm::rotate(glm::mat4{ 1.0f }, m_Transform.Rotation.x, glm::vec3{ 1.0f, 0.0f, 0.0f })
			* glm::rotate(glm::mat4{ 1.0f }, m_Transform.Rotation.y, glm::vec3{ 0.0f, 1.0f, 0.0f })
			* glm::rotate(glm::mat4{ 1.0f }, m_Transform.Rotation.z, glm::vec3{ 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4{ 1.0f }, m_Transform.Scale);
	}

}
