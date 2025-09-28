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

	class Model
	{
	public:
		static auto Create(const std::vector<UUID> meshIDs, const std::unordered_map<std::string, Ref<Texture2D>> textures) -> Ref<Model>;

		Model(const std::vector<UUID> meshIDs, const std::unordered_map<std::string, Ref<Texture2D>> textures);


		auto ModelID() const -> const UUID { return m_ModelID; }

	private:
		UUID m_ModelID{};

		std::vector<UUID> m_MeshIDs{};

		std::unordered_map<std::string, Ref<Texture2D>> m_Textures{};
	};

}
