#include "Scene/Entity.h"

#include "Renderer/Mesh.h"


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


	auto Entity::Draw() -> void
	{

//		m_Texture->BindToSlot(0);

//		m_Mesh->Draw();
	}

}
