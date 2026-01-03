#include "Scene/Model.h"


namespace Nut
{


	auto Model::Create(const std::vector<UUID> meshIDs, const std::unordered_map<TextureType, Texture2D&>& textures) -> Model
	{
		return Model{ meshIDs, textures };
	}

	Model::Model(const Model& other)
	{
		m_ModelID = other.m_ModelID;
		m_MeshIDs = other.m_MeshIDs;
		m_Textures = other.m_Textures;
	}

	Model::Model(const std::vector<UUID> meshIDs, const std::unordered_map<TextureType, Texture2D&>& textures)
		: m_MeshIDs(meshIDs), m_Textures(textures)
	{

	}



}
