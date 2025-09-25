#pragma once

#include "Core/Base.h"
#include "Core/UUID.h"


namespace Nut
{


	class Mesh;

	class AssetManager
	{
	public:
		static auto AddMesh(Ref<Mesh> mesh) -> const UUID;
		static auto GetMesh(UUID uuid) -> Ref<Mesh>;
	};

}
