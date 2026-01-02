#include "Scene/Entity.h"

#include "Assets/AssetManager.h"
#include "Renderer/Mesh.h"
#include "Scene/Model.h"

#include <glm/gtc/matrix_transform.hpp>


namespace Nut
{



	auto EntityTransform::CalculateTransformMatrix() -> const glm::mat4&
	{
		TransformMatrix = glm::mat4(1.0f) * glm::translate(glm::mat4(1.0f), Position)
			* glm::rotate(glm::mat4{ 1.0f }, Rotation.x, glm::vec3{ 1.0f, 0.0f, 0.0f })
			* glm::rotate(glm::mat4{ 1.0f }, Rotation.y, glm::vec3{ 0.0f, 1.0f, 0.0f })
			* glm::rotate(glm::mat4{ 1.0f }, Rotation.z, glm::vec3{ 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4{ 1.0f }, Scale);

		return TransformMatrix;
	}



	auto Entity::Create(UUID modelID) -> Ref<Entity>
	{
		return CreateRef<Entity>(modelID);
	}

	Entity::Entity(UUID modelID)
		: m_ModelID(modelID)
	{

	}

	auto Entity::CreateDebugLines(std::vector<LineVertex>& vertexList) -> void
	{
		auto model = AssetManager<Ref<Model>>::Get(m_ModelID);

		auto meshIDs = model->MeshIDs();

		for (auto& meshID : meshIDs)
		{
			auto mesh = AssetManager<Ref<Mesh>>::Get(meshID);
			mesh->CreateDebugLines(vertexList, m_Transform.TransformMatrix);
		}
	}

}
