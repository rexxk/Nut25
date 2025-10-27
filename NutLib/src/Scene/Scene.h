#pragma once


#include "Core/Base.h"
#include "Scene/Entity.h"


namespace Nut
{


	class Model;

	class Scene
	{
	public:
		Scene();

		auto Update(double ts) -> void;
		auto Draw() -> void;

		auto AddEntity(Ref<Entity> entity) -> void;
		auto SetTerrainEntity(Ref<Entity> terrainEntity) -> void;

		auto SetTerrainModel(Ref<Model> terrainModel) -> void;
	};


}
