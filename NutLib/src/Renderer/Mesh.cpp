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

	auto CalculateNormals(uint32_t width, uint32_t height, std::vector<Vertex>& vertices) -> void
	{
		for (auto z = 0u; z < height - 1; z++)
		{
			for (auto x = 0u; x < width - 1; x++)
			{
				auto v1 = (width * z) + x;
				auto v2 = (width * z) + (x + 1);
				auto v3 = (width * (z + 1)) + x;
				auto v4 = (width * (z + 1)) + (x + 1);

				{
					glm::vec3& p1 = vertices[v1].Position;
					glm::vec3& p2 = vertices[v2].Position;
					glm::vec3& p3 = vertices[v3].Position;

					auto normal = glm::normalize(glm::cross(p3 - p1, p2 - p1));

					vertices[v1].Normal += normal;
					vertices[v2].Normal += normal;
					vertices[v3].Normal += normal;

					vertices[v1].Normal /= 2.0f;
					vertices[v2].Normal /= 2.0f;
					vertices[v3].Normal /= 2.0f;
				}

				{
					glm::vec3& p1 = vertices[v4].Position;
					glm::vec3& p2 = vertices[v3].Position;
					glm::vec3& p3 = vertices[v2].Position;

					auto normal = glm::normalize(glm::cross(p3 - p1, p2 - p1));

					vertices[v4].Normal += normal;
					vertices[v3].Normal += normal;
					vertices[v2].Normal += normal;

					vertices[v4].Normal /= 2.0f;
					vertices[v3].Normal /= 2.0f;
					vertices[v2].Normal /= 2.0f;
				}
			}
		}

	}

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

	auto Mesh::CreateFromHeightmapData(const HeightmapSpecification& heightmapSpecification) -> Mesh
	{
		uint32_t index{ 0l };

		std::vector<Vertex> vertices(heightmapSpecification.Width * heightmapSpecification.Height);
		size_t position = 0;

		const float& div1 = heightmapSpecification.NoiseDivider1;
		const float& div2 = heightmapSpecification.NoiseDivider2;
		const float& div3 = heightmapSpecification.NoiseDivider3;

		for (auto z = 0u; z < heightmapSpecification.Height; z++)
		{
			for (auto x = 0u; x < heightmapSpecification.Width; x++)
			{
				auto xScaled = x / heightmapSpecification.Scale;
				auto zScaled = z / heightmapSpecification.Scale;

				float noise = (PerlinNoise::GetNoise(xScaled / div1, zScaled / div1) + PerlinNoise::GetNoise(xScaled / div2, zScaled / div2) * 0.5f + PerlinNoise::GetNoise(xScaled / div3, zScaled / div3) * 0.25f) / heightmapSpecification.Divider;
				float brightness = (noise * 0.5f + 0.5f) * heightmapSpecification.Amplitude - (heightmapSpecification.Amplitude / 2);
//				float brightness = (noise * 0.5f + 0.5f) * 255.0f - 128.0f;

				Vertex v{};
				v.Position = glm::vec3{ static_cast<float>(x) - heightmapSpecification.Width / 2, brightness, static_cast<float>(z) - heightmapSpecification.Height / 2 };

				v.TexCoord = glm::vec2{ x / static_cast<float>(heightmapSpecification.Width), 1.0f - (z / static_cast<float>(heightmapSpecification.Height)) };
				v.TexCoord *= heightmapSpecification.TextureMultiplier;
				v.Normal = glm::vec3{ 0.0f };
				v.Color = glm::vec4{ 1.0f };

				vertices[position++] = v;
			}
		}

		std::vector<uint32_t> indices(heightmapSpecification.Width * heightmapSpecification.Height * 6);
		index = 0u;

		for (auto z = 0u; z < heightmapSpecification.Height - 1; z++)
		{
			for (auto x = 0u; x < heightmapSpecification.Width - 1; x++)
			{
				auto v1 = (heightmapSpecification.Width * z) + x;
				auto v2 = (heightmapSpecification.Width * z) + (x + 1);
				auto v3 = (heightmapSpecification.Width * (z + 1)) + x;
				auto v4 = (heightmapSpecification.Width * (z + 1)) + (x + 1);

				indices[index++] = v1;
				indices[index++] = v2;
				indices[index++] = v3;

				indices[index++] = v4;
				indices[index++] = v3;
				indices[index++] = v2;
			}
		}

		CalculateNormals(heightmapSpecification.Width, heightmapSpecification.Height, vertices);

		return Mesh{ vertices, indices, "Terrain" };
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

	auto Mesh::UpdateFromHeightmapData(Mesh& mesh, const HeightmapSpecification& heightmapSpecification) -> void
	{
		uint32_t index{ 0u };

		size_t position = 0;

		auto& vertices = mesh.GetVertices();

		const float& div1 = heightmapSpecification.NoiseDivider1;
		const float& div2 = heightmapSpecification.NoiseDivider2;
		const float& div3 = heightmapSpecification.NoiseDivider3;

		for (auto z = 0u; z < heightmapSpecification.Height; z++)
		{
			for (auto x = 0u; x < heightmapSpecification.Width; x++)
			{
				auto xScaled = x / heightmapSpecification.Scale;
				auto zScaled = z / heightmapSpecification.Scale;

				float noise = (PerlinNoise::GetNoise(xScaled / div1, zScaled / div1) + PerlinNoise::GetNoise(xScaled / div2, zScaled / div2) * 0.5f + PerlinNoise::GetNoise(xScaled / div3, zScaled / div3) * 0.25f) / heightmapSpecification.Divider;
				float brightness = (noise * 0.5f + 0.5f) * heightmapSpecification.Amplitude - (heightmapSpecification.Amplitude / 2);
				//				float brightness = (noise * 0.5f + 0.5f) * 255.0f - 128.0f;

				Vertex& v = vertices[z * heightmapSpecification.Width + x];
				//				v.Position = glm::vec3{ static_cast<float>(x) - width / 2, brightness, static_cast<float>(z) - height / 2 };
				v.Position.y = brightness;

				v.TexCoord = glm::vec2{ x / static_cast<float>(heightmapSpecification.Width), 1.0f - (z / static_cast<float>(heightmapSpecification.Height)) };
				v.TexCoord *= heightmapSpecification.TextureMultiplier;
			}
		}

		CalculateNormals(heightmapSpecification.Width, heightmapSpecification.Height, vertices);
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
