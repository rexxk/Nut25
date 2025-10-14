#pragma once

#include "Core/Base.h"
#include "Core/UUID.h"

//#include "Renderer/OpenGLBuffer.h"
//#include "Renderer/OpenGLShader.h"
#include "Renderer/Renderer.h"

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

#include <glad/glad.h>


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


	class Mesh
	{
	public:
		static auto Create(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::string& name = "<mesh>") -> Ref<Mesh>;

		static auto CreateTriangle() -> Ref<Mesh>;
		static auto CreateRectangle() -> Ref<Mesh>;
		static auto CreatePlane(uint32_t width, uint32_t height, const HeightmapSpecification& specification) -> Ref<Mesh>;

		Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::string& name = "<mesh>");
		~Mesh();

		auto UpdateHeightmap(const HeightmapSpecification& specification) -> void;

		auto GetVertices() const -> const std::vector<Vertex>& { return m_Vertices; }
		auto GetIndices() const -> const std::vector<uint32_t>& { return m_Indices; }

		auto MeshID() const -> const UUID { return m_MeshID; }

		auto Name() const -> const std::string { return m_Name; }


	private:

		std::vector<Vertex> m_Vertices{};
		std::vector<uint32_t> m_Indices{};

		UUID m_MeshID{};

		std::string m_Name{};
	};


}
