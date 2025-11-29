#include "Scene/Model.h"

#include <print>

namespace Nut
{


	auto Model::Create(const std::vector<UUID> meshIDs, const std::unordered_map<TextureType, Ref<Texture2D>> textures) -> Ref<Model>
	{
		return CreateRef<Model>(meshIDs, textures);
	}


	Model::Model(const std::vector<UUID> meshIDs, const std::unordered_map<TextureType, Ref<Texture2D>> textures)
		: m_MeshIDs(meshIDs), m_Textures(textures)
	{
		std::println("Terrain ID: {}", static_cast<uint64_t>(meshIDs[0]));

	}


}
