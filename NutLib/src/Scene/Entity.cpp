#include "Scene/Entity.h"

#include "Assets/AssetManager.h"
#include "Renderer/Mesh.h"
#include "Scene/Components.h"
#include "Scene/Model.h"

#include <glm/gtc/matrix_transform.hpp>


namespace Nut
{




	auto Entity::Create(UUID modelID, const std::string& tag) -> Ref<Entity>
	{
		return CreateRef<Entity>(modelID, tag);
	}

	Entity::Entity(UUID modelID, const std::string& tag)
		: m_ModelID(modelID)
	{
		AddComponent<TagComponent>(TagComponent{ .Tag{tag} });
	}

	auto Entity::CreateDebugLines(std::vector<LineVertex>& vertexList) -> void
	{
		if (HasComponent<MeshComponent>())
		{
			auto& meshComponent = GetComponent<MeshComponent>();

			for (auto& [meshID, localTransform] : meshComponent.Meshes)
			{
				auto& mesh = AssetManager<Scope<Mesh>>::Get(meshID);
				auto& transform = GetComponent<TransformComponent>();
				mesh->CreateDebugLines(vertexList, transform.CalculateTransformMatrix() * localTransform.TransformMatrix);
			}
		}

	}

}
