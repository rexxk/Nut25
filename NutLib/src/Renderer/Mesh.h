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

#include <glm/glm.hpp>


namespace Nut
{


	struct AABB
	{
		glm::vec3 Center{ 0.0f };
		glm::vec3 Extents{ 0.0f };

		auto CreateDebugLineMesh(std::vector<LineVertex>& lineVertices, const glm::mat4& transformMatrix, bool OnFrustum) const -> void;
	};


	class Mesh
	{
	public:
		static auto Create(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::string& name = "<mesh>") -> Mesh;

		static auto CreateTriangle() -> Mesh;
		static auto CreateRectangle() -> Mesh;

		Mesh() = default;
		Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::string& name = "<mesh>");
		virtual ~Mesh();

		auto GetVertices() const -> const std::vector<Vertex>& { return m_Vertices; }
		auto GetIndices() const -> const std::vector<uint32_t>& { return m_Indices; }

		auto ID() const -> const UUID { return m_MeshID; }

		auto Name() const -> const std::string { return m_Name; }

		auto GetBoundingBox() const -> const AABB { return m_AABB; }

		auto CreateDebugLines(std::vector<LineVertex>& vertexList, const glm::mat4& transformMatrix) -> void;

	protected:

		std::vector<Vertex> m_Vertices{};
		std::vector<uint32_t> m_Indices{};

		UUID m_MeshID{};

		AABB m_AABB;

		std::string m_Name{};
	};


}
