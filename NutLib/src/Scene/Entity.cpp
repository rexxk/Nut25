#include "Scene/Entity.h"

#include "Assets/AssetManager.h"
#include "Renderer/Mesh.h"
#include "Scene/Components.h"
#include "Scene/Model.h"

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

	auto Entity::CreateDebugLines(std::vector<LineVertex>& vertexList) -> void
	{
		auto& model = AssetManager<Scope<Model>>::Get(m_ModelID);

		auto& meshIDs = model->MeshIDs();

		for (auto& meshID : meshIDs)
		{
			auto& mesh = AssetManager<Scope<Mesh>>::Get(meshID);
			auto& transform = GetComponent<TransformComponent>();
			mesh->CreateDebugLines(vertexList, transform.CalculateTransformMatrix());
		}
	}

}
