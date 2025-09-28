#include "Assets/AssetManager.h"

#include "Core/Base.h"
#include "Core/UUID.h"
#include "Renderer/Mesh.h"
#include "Scene/Model.h"


#include <unordered_map>

namespace Nut
{


	struct AssetLibrary
	{
		std::unordered_map<UUID, Ref<Mesh>> Meshes;
		std::unordered_map<UUID, Ref<Model>> Models;
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


	auto AssetManager::AddModel(Ref<Model> model) -> const UUID
	{
		s_AssetLibrary.Models[model->ModelID()] = model;

		return model->ModelID();
	}

	auto AssetManager::GetModel(UUID uuid) -> Ref<Model>
	{
		if (s_AssetLibrary.Models.contains(uuid))
			return s_AssetLibrary.Models[uuid];

		return nullptr;
	}

}
