#include "Scene/Entity.h"

#include "Renderer/Mesh.h"


namespace Nut
{


	auto Entity::Create(Ref<Mesh> mesh, Ref<Texture2D> texture) -> Ref<Entity>
	{
		return CreateRef<Entity>(mesh, texture);
	}

	Entity::Entity(Ref<Mesh> mesh, Ref<Texture2D> texture)
		: m_Mesh(mesh), m_Texture(texture)
	{

	}


	auto Entity::Draw() -> void
	{

		m_Texture->BindToSlot(0);

		m_Mesh->Draw();
	}

}
