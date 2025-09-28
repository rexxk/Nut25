#pragma once

#include "Core/Base.h"
#include "Core/UUID.h"


namespace Nut
{


	class Mesh;
	class Model;

	class AssetManager
	{
	public:
		static auto AddMesh(Ref<Mesh> mesh) -> const UUID;
		static auto GetMesh(UUID uuid) -> Ref<Mesh>;

		static auto AddModel(Ref<Model> model) -> const UUID;
		static auto GetModel(UUID uuid) -> Ref<Model>;
	};

}
