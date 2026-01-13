#include "Renderer/TerrainMesh.h"

#include "Noise/PerlinNoise.h"

#include <stb_image.h>


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



	auto TerrainMesh::Create(uint32_t width, uint32_t height, const HeightmapSpecification& specification) -> Mesh
	{
		return TerrainMesh{ width, height, specification };
	}


	TerrainMesh::TerrainMesh(uint32_t width, uint32_t height, const HeightmapSpecification& specification)
		: Mesh(), m_Width(width), m_Height(height)
	{
		uint32_t index{ 0l };

		m_Vertices.resize(width * height);
		size_t position = 0;

		const float& div1 = specification.NoiseDivider1;
		const float& div2 = specification.NoiseDivider2;
		const float& div3 = specification.NoiseDivider3;

		if (specification.UseNoise)
		{
			for (auto z = 0u; z < height; z++)
			{
				for (auto x = 0u; x < width; x++)
				{
					auto xScaled = x / specification.Scale;
					auto zScaled = z / specification.Scale;

					float noise = (PerlinNoise::GetNoise(xScaled / div1, zScaled / div1) + PerlinNoise::GetNoise(xScaled / div2, zScaled / div2) * 0.5f + PerlinNoise::GetNoise(xScaled / div3, zScaled / div3) * 0.25f) / specification.Divider;
					float brightness = (noise * 0.5f + 0.5f) * specification.Amplitude - (specification.Amplitude / 2);
//					float brightness = (noise * 0.5f + 0.5f) * 255.0f - 128.0f;

					Vertex v{};
					v.Position = glm::vec3{ static_cast<float>(x) - width / 2, brightness, static_cast<float>(z) - height / 2 };

					v.TexCoord = glm::vec2{ x / static_cast<float>(width), 1.0f - (z / static_cast<float>(height)) };
					v.TexCoord *= specification.TextureMultiplier;
					v.Normal = glm::vec3{ 0.0f };
					v.Color = glm::vec4{ 1.0f };

					m_Vertices[position++] = v;
				}
			}
		}
		else
		{
			int width{ 0 };
			int height{ 0 };
			int bitsPerPixel{ 0 };

			stbi_set_flip_vertically_on_load(true);
			auto pixels = stbi_load(specification.Filepath.string().c_str(), &width, &height, &bitsPerPixel, 4);

			for (auto z = 0; z < height; z++)
			{
				for (auto x = 0; x < width; x++)
				{
					Vertex v{};

					v.Position = glm::vec3{ static_cast<float>(x) - width / 2, (pixels[(z * width + x) * 4]) - 225.0f, static_cast<float>(z) - height / 2 };
					v.TexCoord = glm::vec2{ std::abs(x) % 2, std::abs(z) % 2 };
					v.Normal = glm::vec3{ 0.0f, 1.0f, 0.0f };
					v.Color = glm::vec4{ 1.0f };

					m_Vertices[position++] = v;
				}
			}

			stbi_image_free(pixels);
		}

		m_Indices.resize(width * height * 6);
		index = 0u;

		for (auto z = 0u; z < height - 1; z++)
		{
			for (auto x = 0u; x < width - 1; x++)
			{
				auto v1 = (width * z) + x;
				auto v2 = (width * z) + (x + 1);
				auto v3 = (width * (z + 1)) + x;
				auto v4 = (width * (z + 1)) + (x + 1);

				m_Indices[index++] = v1;
				m_Indices[index++] = v2;
				m_Indices[index++] = v3;

				m_Indices[index++] = v4;
				m_Indices[index++] = v3;
				m_Indices[index++] = v2;
			}
		}

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

		CalculateNormals(width, height, m_Vertices);
	}


	auto TerrainMesh::UpdateHeightmap(const HeightmapSpecification& specification) -> void
	{
		uint32_t index{ 0u };

		size_t position = 0;

		const float& div1 = specification.NoiseDivider1;
		const float& div2 = specification.NoiseDivider2;
		const float& div3 = specification.NoiseDivider3;

		for (auto z = 0u; z < m_Height; z++)
		{
			for (auto x = 0u; x < m_Width; x++)
			{
				auto xScaled = x / specification.Scale;
				auto zScaled = z / specification.Scale;

				float noise = (PerlinNoise::GetNoise(xScaled / div1, zScaled / div1) + PerlinNoise::GetNoise(xScaled / div2, zScaled / div2) * 0.5f + PerlinNoise::GetNoise(xScaled / div3, zScaled / div3) * 0.25f) / specification.Divider;
				float brightness = (noise * 0.5f + 0.5f) * specification.Amplitude - (specification.Amplitude / 2);
//				float brightness = (noise * 0.5f + 0.5f) * 255.0f - 128.0f;

				Vertex& v = m_Vertices[z * m_Width + x];
				//				v.Position = glm::vec3{ static_cast<float>(x) - width / 2, brightness, static_cast<float>(z) - height / 2 };
				v.Position.y = brightness;

				v.TexCoord = glm::vec2{ x / static_cast<float>(m_Width), 1.0f - (z / static_cast<float>(m_Height)) };
				v.TexCoord *= specification.TextureMultiplier;
			}
		}

		CalculateNormals(m_Width, m_Height, m_Vertices);

	}



}
