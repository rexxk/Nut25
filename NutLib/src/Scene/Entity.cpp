#include "Scene/Entity.h"

#include "Renderer/Mesh.h"


namespace Nut
{


	auto Entity::Create(Ref<Mesh> mesh) -> Ref<Entity>
	{
		return CreateRef<Entity>(mesh);
	}

	Entity::Entity(Ref<Mesh> mesh)
		: m_Mesh(mesh)
	{

	}


}
