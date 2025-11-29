#include "Renderer/Mesh.h"

#include "Noise/PerlinNoise.h"
#include "Renderer/OpenGLShader.h"
#include "Renderer/Renderer.h"

#include <stb_image.h>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Nut
{


	auto Mesh::Create(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::string& name) -> Ref<Mesh>
	{
		return CreateRef<Mesh>(vertices, indices, name);
	}

	auto Mesh::CreateTriangle() -> Ref<Mesh>
	{
		std::vector<Nut::Vertex> vertices{
			{.Position{ -0.5f, -0.5f, 0.0f }, .TexCoord{ 0.0f, 0.0f }, .Normal{0.0f, 0.0f, 1.0f}, .Color{ 1.0f, 0.0f, 0.0f, 1.0f }},
			{.Position{  0.5f, -0.5f, 0.0f }, .TexCoord{ 1.0f, 0.0f }, .Normal{0.0f, 0.0f, 1.0f}, .Color{ 0.0f, 1.0f, 0.0f, 1.0f }},
			{.Position{  0.0f,  0.5f, 0.0f }, .TexCoord{ 1.0f, 1.0f }, .Normal{0.0f, 0.0f, 1.0f}, .Color{ 0.0f, 0.0f, 1.0f, 1.0f }},
		};

		std::vector<uint32_t> indices{
			0, 1, 2,
		};

		return CreateRef<Mesh>(vertices, indices, "Triangle");
	}

	auto Mesh::CreateRectangle() -> Ref<Mesh>
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

		return CreateRef<Mesh>(vertices, indices, "Rectangle");

	}

	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::string& name)
		: m_Vertices(vertices), m_Indices(indices), m_Name(name)
	{
		for (auto& vertex : m_Vertices)
		{
			m_AABB.Min.x = std::min(m_AABB.Min.x, vertex.Position.x);
			m_AABB.Min.y = std::min(m_AABB.Min.y, vertex.Position.y);
			m_AABB.Min.z = std::min(m_AABB.Min.z, vertex.Position.z);

			m_AABB.Max.x = std::max(m_AABB.Max.x, vertex.Position.x);
			m_AABB.Max.y = std::max(m_AABB.Max.y, vertex.Position.y);
			m_AABB.Max.z = std::max(m_AABB.Max.z, vertex.Position.z);
		}
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
