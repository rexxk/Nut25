#pragma once

#include "Core/Base.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

#include <unordered_map>
#include <vector>

namespace Nut
{

	enum class MaterialType
	{
		AlbedoTexture,
		NormalMap,
		MetalnessMap,
		RoughnessMap,

		TerrainGrass,
		TerrainDirt,
		TerrainStone,
		TerrainSnow,
	};


	class Material
	{
	public:
		Material() = default;
		Material(Ref<Shader> shader);


	private:
		Ref<Shader> m_Shader{ nullptr };

		std::unordered_map<MaterialType, std::vector<Ref<Texture2D>>> m_Textures{};
	};


}
