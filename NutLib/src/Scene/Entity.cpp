#include "Scene/Entity.h"

#include "Renderer/Mesh.h"


namespace Nut
{


	auto Entity::Create(UUID meshID, Ref<Texture2D> texture) -> Ref<Entity>
	{
		return CreateRef<Entity>(meshID, texture);
	}

	Entity::Entity(UUID meshID, Ref<Texture2D> texture)
		: m_MeshID(meshID), m_Texture(texture)
	{

	}


	auto Entity::Draw() -> void
	{

		m_Texture->BindToSlot(0);

//		m_Mesh->Draw();
	}

}
