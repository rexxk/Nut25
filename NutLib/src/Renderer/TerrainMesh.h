#pragma once

#include "Renderer/Mesh.h"

#include <cstdint>


namespace Nut
{


	struct HeightmapSpecification
	{
		bool UseNoise{ true };

		float NoiseDivider1{ 64.0f };
		float NoiseDivider2{ 32.0f };
		float NoiseDivider3{ 16.0f };
		float Divider{ 1.75f };

		std::filesystem::path Filepath{};
	};


	class TerrainMesh : public Mesh
	{
	public:
		static auto Create(uint32_t width, uint32_t height, const HeightmapSpecification& specification) -> Ref<Mesh>;

		TerrainMesh(uint32_t width, uint32_t height, const HeightmapSpecification& specification);

		auto UpdateHeightmap(const HeightmapSpecification& specification) -> void;


	private:
		uint32_t m_Width{};
		uint32_t m_Height{};

	};



}
