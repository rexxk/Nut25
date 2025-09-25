#include "Assets/AssetManager.h"

#include "Core/Base.h"
#include "Core/UUID.h"
#include "Renderer/Mesh.h"


#include <unordered_map>

namespace Nut
{


	struct AssetLibrary
	{
		std::unordered_map<UUID, Ref<Mesh>> Meshes;
	};

	static AssetLibrary s_AssetLibrary;


	auto AssetManager::AddMesh(Ref<Mesh> mesh) -> const UUID
	{
		s_AssetLibrary.Meshes[mesh->MeshID()] = mesh;

		return mesh->MeshID();
	}

	auto AssetManager::GetMesh(UUID uuid) -> Ref<Mesh>
	{
		if (s_AssetLibrary.Meshes.contains(uuid))
			return s_AssetLibrary.Meshes[uuid];

		return nullptr;
	}

}
