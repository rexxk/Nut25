#include "Renderer/Mesh.h"

#include "Noise/PerlinNoise.h"
#include "Renderer/OpenGLShader.h"
#include "Renderer/Renderer.h"

#include <stb_image.h>

#include <glad/glad.h>


namespace Nut
{


	auto Mesh::Create(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::string& name) -> Ref<Mesh>
	{
		return CreateRef<Mesh>(vertices, indices, name);
	}

	auto Mesh::CreateTriangle() -> Ref<Mesh>
	{
		std::vector<Nut::Vertex> vertices{
			{.Position{ -0.5f, -0.5f, 0.0f }, .TexCoord{ 0.0f, 0.0f }, .Normal{0.0f, 0.0f, -1.0f}, .Color{ 1.0f, 0.0f, 0.0f, 1.0f }},
			{.Position{  0.5f, -0.5f, 0.0f }, .TexCoord{ 1.0f, 0.0f }, .Normal{0.0f, 0.0f, -1.0f}, .Color{ 0.0f, 1.0f, 0.0f, 1.0f }},
			{.Position{  0.0f,  0.5f, 0.0f }, .TexCoord{ 1.0f, 1.0f }, .Normal{0.0f, 0.0f, -1.0f}, .Color{ 0.0f, 0.0f, 1.0f, 1.0f }},
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
			{.Position{-1.0f, -1.0f, 0.0f}, .TexCoord{0.0f, 0.0f}, .Normal{0.0f, 0.0f, -1.0f},},
			{.Position{ 1.0f, -1.0f, 0.0f}, .TexCoord{1.0f, 0.0f}, .Normal{0.0f, 0.0f, -1.0f},},
			{.Position{ 1.0f,  1.0f, 0.0f}, .TexCoord{1.0f, 1.0f}, .Normal{0.0f, 0.0f, -1.0f},},
			{.Position{-1.0f,  1.0f, 0.0f}, .TexCoord{0.0f, 1.0f}, .Normal{0.0f, 0.0f, -1.0f},},
		};

		std::vector<uint32_t> indices
		{
			0, 1, 2, 2, 3, 0,
		};

		return CreateRef<Mesh>(vertices, indices, "Rectangle");

	}


	auto Mesh::CreatePlane(uint32_t width, uint32_t height, const HeightmapSpecification& specification) -> Ref<Mesh>
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

		uint32_t index{ 0l };

		vertices.resize(width * height);
		size_t position = 0;

		if (specification.UseNoise)
		{
			for (auto z = 0u; z < height; z++)
			{
				for (auto x = 0u; x < width; x++)
				{
					float div1 = specification.NoiseDivider1;
					float div2 = specification.NoiseDivider2;
					float div3 = specification.NoiseDivider3;

					float noise = (PerlinNoise::GetNoise(x / div1, z / div1) + PerlinNoise::GetNoise(x / div2, z / div2) * 0.5f + PerlinNoise::GetNoise(x / div3, z / div3) * 0.25f) / specification.Divider;
					float brightness = (noise * 0.5f + 0.5f) * 255.0f - 128.0f;

					Vertex v{};
					v.Position = glm::vec3{ static_cast<float>(x) - width / 2, brightness, static_cast<float>(z) - height / 2 };
					v.TexCoord = glm::vec2{ x % 2, z % 2 };
					v.Normal = glm::vec3{ 0.0f };
//					v.Normal = glm::vec3{ 0.0f, 1.0f, 0.0f };
					v.Color = glm::vec4{ 1.0f };

					vertices[position++] = v;
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

					v.Position = glm::vec3{ static_cast<float>(x) - width / 2, (pixels[(z * width + x) * 4]) - 225.0f, static_cast<float>(z) - height / 2};
					v.TexCoord = glm::vec2{ std::abs(x) % 2, std::abs(z) % 2 };
					v.Normal = glm::vec3{ 0.0f, 1.0f, 0.0f };
					v.Color = glm::vec4{ 1.0f };

					vertices[position++] = v;
				}
			}

			stbi_image_free(pixels);
		}

		indices.resize(width * height * 6);
		index = 0l;
		for (auto z = 0u; z < height - 1; z++)
		{
			for (auto x = 0u; x < width - 1; x++)
			{
				auto v1 = (width * z) + x;
				auto v2 = (width * z) + (x + 1);
				auto v3 = (width * (z + 1)) + x;
				auto v4 = (width * (z + 1)) + (x + 1);

				indices[index++] = v1;
				indices[index++] = v2;
				indices[index++] = v3;

				{
					glm::vec3& p1 = vertices[v1].Position;
					glm::vec3& p2 = vertices[v2].Position;
					glm::vec3& p3 = vertices[v3].Position;

					auto normal = glm::normalize(glm::cross(p1 - p2, p1 - p3));

					vertices[v1].Normal += normal;
					vertices[v2].Normal += normal;
					vertices[v3].Normal += normal;

					vertices[v1].Normal /= 2.0f;
					vertices[v2].Normal /= 2.0f;
					vertices[v3].Normal /= 2.0f;
				}

				indices[index++] = v4;
				indices[index++] = v3;
				indices[index++] = v2;

				{
					glm::vec3& p1 = vertices[v4].Position;
					glm::vec3& p2 = vertices[v3].Position;
					glm::vec3& p3 = vertices[v2].Position;

					auto normal = glm::normalize(glm::cross(p1 - p2, p1 - p3));

					vertices[v4].Normal += normal;
					vertices[v3].Normal += normal;
					vertices[v2].Normal += normal;

					vertices[v4].Normal /= 2.0f;
					vertices[v3].Normal /= 2.0f;
					vertices[v2].Normal /= 2.0f;
				}
			}
		}

		return CreateRef<Mesh>(vertices, indices, "Plane");
	}

	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::string& name)
		: m_Vertices(vertices), m_Indices(indices), m_Name(name)
	{

	}

	Mesh::~Mesh()
	{

	}


}
