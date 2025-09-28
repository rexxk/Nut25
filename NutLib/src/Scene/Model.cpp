#include "Scene/Model.h"



namespace Nut
{


	auto Model::Create(const std::vector<UUID> meshIDs, const std::unordered_map<std::string, Ref<Texture2D>> textures) -> Ref<Model>
	{
		return CreateRef<Model>(meshIDs, textures);
	}


	Model::Model(const std::vector<UUID> meshIDs, const std::unordered_map<std::string, Ref<Texture2D>> textures)
		: m_MeshIDs(meshIDs), m_Textures(textures)
	{

	}


}
