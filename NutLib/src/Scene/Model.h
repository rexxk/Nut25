#pragma once

#include "Core/Base.h"
#include "Core/UUID.h"
#include "Renderer/Mesh.h"
#include "Renderer/Texture.h"

#include <string>
#include <unordered_map>
#include <vector>


namespace Nut
{


	enum class TextureType : uint8_t
	{
		Albedo = 0,
		Normal,
		Metalness,
		Roughness,
		AmbientOcclusion,
	};


	class Model
	{
	public:
		static auto Create(const std::vector<UUID> meshIDs, const std::unordered_map<TextureType, Ref<Texture2D>> textures) -> Ref<Model>;

		Model(const std::vector<UUID> meshIDs, const std::unordered_map<TextureType, Ref<Texture2D>> textures);


		auto ModelID() const -> const UUID { return m_ModelID; }
		auto ID() const -> const UUID { return m_ModelID; }
		auto MeshIDs() const -> const std::vector<UUID> { return m_MeshIDs; }

		auto GetTextures() -> const std::unordered_map<TextureType, Ref<Texture2D>>& { return m_Textures; }

	private:
		UUID m_ModelID{};

		std::vector<UUID> m_MeshIDs{};

		std::unordered_map<TextureType, Ref<Texture2D>> m_Textures{};
	};

}
