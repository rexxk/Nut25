#include "Scene/Model.h"

#include "Core/Base.h"


namespace Nut
{


	auto Model::Create(const std::vector<UUID>& meshIDs, const std::unordered_map<TextureType, Scope<Texture2D>&>& textures) -> Scope<Model>
	{
		return CreateScope<Model>(meshIDs, textures);
	}

	Model::Model(const Model& other)
	{
		m_ModelID = other.m_ModelID;
		m_MeshIDs = other.m_MeshIDs;
//		m_Textures = other.m_Textures;
	}

	Model::Model(const std::vector<UUID>& meshIDs, const std::unordered_map<TextureType, Scope<Texture2D>&>& textures)
		: m_MeshIDs(meshIDs), m_Textures(textures)
	{

	}



}
