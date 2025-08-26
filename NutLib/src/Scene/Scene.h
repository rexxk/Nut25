#pragma once


#include "Core/Base.h"
#include "Scene/Entity.h"


namespace Nut
{


	class Scene
	{
	public:
		Scene();

		auto Draw() -> void;

		auto AddEntity(Ref<Entity> entity) -> void;

	};


}
