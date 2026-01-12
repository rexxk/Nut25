#include "Renderer/Mesh.h"

#include "Noise/PerlinNoise.h"
#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"

#include <stb_image.h>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Nut
{

	auto AABB::CreateDebugLineMesh(std::vector<LineVertex>& lineVertices, const glm::mat4& transformMatrix, bool OnFrustum) const -> void
	{
		LineVertex newVertex{ .Color = {0.0f, 1.0f, 0.0f, 1.0f} };

		if (!OnFrustum)
			newVertex.Color = { 1.0f, 0.0f, 0.0f, 1.0f };

		auto p1 = transformMatrix * glm::vec4{ glm::vec3{ Center.x - Extents.x, Center.y - Extents.y, Center.z - Extents.z }, 1.0f };
		auto p2 = transformMatrix * glm::vec4{ glm::vec3{ Center.x + Extents.x, Center.y - Extents.y, Center.z - Extents.z }, 1.0f };
		auto p3 = transformMatrix * glm::vec4{ glm::vec3{ Center.x + Extents.x, Center.y + Extents.y, Center.z - Extents.z }, 1.0f };
		auto p4 = transformMatrix * glm::vec4{ glm::vec3{ Center.x - Extents.x, Center.y + Extents.y, Center.z - Extents.z }, 1.0f };

		auto p5 = transformMatrix * glm::vec4{ glm::vec3{ Center.x - Extents.x, Center.y - Extents.y, Center.z + Extents.z }, 1.0f };
		auto p6 = transformMatrix * glm::vec4{ glm::vec3{ Center.x + Extents.x, Center.y - Extents.y, Center.z + Extents.z }, 1.0f };
		auto p7 = transformMatrix * glm::vec4{ glm::vec3{ Center.x + Extents.x, Center.y + Extents.y, Center.z + Extents.z }, 1.0f };
		auto p8 = transformMatrix * glm::vec4{ glm::vec3{ Center.x - Extents.x, Center.y + Extents.y, Center.z + Extents.z }, 1.0f };

		newVertex.Position = p1;
		lineVertices.push_back(newVertex);
		newVertex.Position = p2;
		lineVertices.push_back(newVertex);

		newVertex.Position = p2;
		lineVertices.push_back(newVertex);
		newVertex.Position = p3;
		lineVertices.push_back(newVertex);

		newVertex.Position = p3;
		lineVertices.push_back(newVertex);
		newVertex.Position = p4;
		lineVertices.push_back(newVertex);

		newVertex.Position = p4;
		lineVertices.push_back(newVertex);
		newVertex.Position = p1;
		lineVertices.push_back(newVertex);


		newVertex.Position = p5;
		lineVertices.push_back(newVertex);
		newVertex.Position = p6;
		lineVertices.push_back(newVertex);

		newVertex.Position = p6;
		lineVertices.push_back(newVertex);
		newVertex.Position = p7;
		lineVertices.push_back(newVertex);

		newVertex.Position = p7;
		lineVertices.push_back(newVertex);
		newVertex.Position = p8;
		lineVertices.push_back(newVertex);

		newVertex.Position = p8;
		lineVertices.push_back(newVertex);
		newVertex.Position = p5;
		lineVertices.push_back(newVertex);


		newVertex.Position = p1;
		lineVertices.push_back(newVertex);
		newVertex.Position = p5;
		lineVertices.push_back(newVertex);

		newVertex.Position = p2;
		lineVertices.push_back(newVertex);
		newVertex.Position = p6;
		lineVertices.push_back(newVertex);

		newVertex.Position = p3;
		lineVertices.push_back(newVertex);
		newVertex.Position = p7;
		lineVertices.push_back(newVertex);

		newVertex.Position = p4;
		lineVertices.push_back(newVertex);
		newVertex.Position = p8;
		lineVertices.push_back(newVertex);
	}



	auto Mesh::Create(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::string& name) -> Mesh
	{
		return Mesh{ vertices, indices, name };
	}

	auto Mesh::CreateTriangle() -> Mesh
	{
		std::vector<Nut::Vertex> vertices{
			{.Position{ -0.5f, -0.5f, 0.0f }, .TexCoord{ 0.0f, 0.0f }, .Normal{0.0f, 0.0f, 1.0f}, .Color{ 1.0f, 0.0f, 0.0f, 1.0f }},
			{.Position{  0.5f, -0.5f, 0.0f }, .TexCoord{ 1.0f, 0.0f }, .Normal{0.0f, 0.0f, 1.0f}, .Color{ 0.0f, 1.0f, 0.0f, 1.0f }},
			{.Position{  0.0f,  0.5f, 0.0f }, .TexCoord{ 1.0f, 1.0f }, .Normal{0.0f, 0.0f, 1.0f}, .Color{ 0.0f, 0.0f, 1.0f, 1.0f }},
		};

		std::vector<uint32_t> indices{
			0, 1, 2,
		};

		return Mesh{ vertices, indices, "Triangle" };
	}

	auto Mesh::CreateRectangle() -> Mesh
	{
		std::vector<Vertex> vertices
		{
			{.Position{-1.0f, -1.0f, 0.0f}, .TexCoord{0.0f, 0.0f}, .Normal{0.0f, 0.0f, 1.0f}, .Color{1.0f}},
			{.Position{ 1.0f, -1.0f, 0.0f}, .TexCoord{1.0f, 0.0f}, .Normal{0.0f, 0.0f, 1.0f}, .Color{1.0f}},
			{.Position{ 1.0f,  1.0f, 0.0f}, .TexCoord{1.0f, 1.0f}, .Normal{0.0f, 0.0f, 1.0f}, .Color{1.0f}},
			{.Position{-1.0f,  1.0f, 0.0f}, .TexCoord{0.0f, 1.0f}, .Normal{0.0f, 0.0f, 1.0f}, .Color{1.0f}},
		};

		std::vector<uint32_t> indices
		{
			0, 1, 2, 2, 3, 0,
		};

		return Mesh{ vertices, indices, "Rectangle" };

	}

	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::string& name)
		: m_Vertices(vertices), m_Indices(indices), m_Name(name)
	{
		// Calculate AABB

		glm::vec3 min{ std::numeric_limits<float>::max() };
		glm::vec3 max{ std::numeric_limits<float>::min() };
		
		for (auto& vertex : m_Vertices)
		{
			min.x = std::min(min.x, vertex.Position.x);
			min.y = std::min(min.y, vertex.Position.y);
			min.z = std::min(min.z, vertex.Position.z);

			max.x = std::max(max.x, vertex.Position.x);
			max.y = std::max(max.y, vertex.Position.y);
			max.z = std::max(max.z, vertex.Position.z);
		}

		m_AABB.Center = (max + min) / 2.0f;
		m_AABB.Extents = { max.x - m_AABB.Center.x, max.y - m_AABB.Center.y, max.z - m_AABB.Center.z };

	}

	Mesh::~Mesh()
	{

	}

	auto Mesh::CreateDebugLines(std::vector<LineVertex>& vertexList, const glm::mat4& transformMatrix) -> void
	{
		for (auto& vertex : m_Vertices)
		{
			glm::vec3 position = glm::vec3{ transformMatrix * glm::vec4{vertex.Position, 1.0f} };
			glm::vec3 normal = glm::mat3(transformMatrix) * vertex.Normal;

			LineVertex v1{ .Position = position, .Color = glm::vec4{1.0f, 1.0f, 0.0f, 1.0f} };
			LineVertex v2{ .Position = position + glm::normalize(normal) * 5.0f, .Color = glm::vec4{1.0f, 1.0f, 0.0f, 1.0f} };

			vertexList.push_back(v1);
			vertexList.push_back(v2);
		}
	}

}
