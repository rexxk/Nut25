#pragma once

#include "Core/Base.h"
#include "Core/UUID.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

#include <unordered_map>
#include <vector>

#include <glm/glm.hpp>


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



	struct MaterialSpecification
	{
		struct MaterialTextures
		{
			UUID Albedo{ 0ull };
			UUID Normal{ 0ull };
			UUID Metalness{ 0ull };
			UUID Roughness{ 0ull };
		} Textures;

		glm::vec4 Color{1.0f, 0.0f, 1.0f, 1.0f};
		float Metalness{ 0.0f };
		float Roughness{ 1.0f };
	};

	class Material
	{
	public:
		static auto Create(Ref<Program> shader, const MaterialSpecification& specification) -> Scope<Material>;

		Material() = default;
		Material(Ref<Program> shader, const MaterialSpecification& specification);
		
		auto GetTextures() -> auto& { return m_Specification.Textures; }

		auto ID() const -> const UUID { return m_ID; }
		auto Shader() -> auto { return m_Shader; }

	private:
		UUID m_ID{};

		Ref<Program> m_Shader{ nullptr };

		MaterialSpecification m_Specification;
	};


}
