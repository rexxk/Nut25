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
			{.Position{-1.0f, -1.0f, 0.0f}, .TexCoord{0.0f, 0.0f}, .Normal{0.0f, 0.0f, -1.0f}, .Color{1.0f}},
			{.Position{ 1.0f, -1.0f, 0.0f}, .TexCoord{1.0f, 0.0f}, .Normal{0.0f, 0.0f, -1.0f}, .Color{1.0f}},
			{.Position{ 1.0f,  1.0f, 0.0f}, .TexCoord{1.0f, 1.0f}, .Normal{0.0f, 0.0f, -1.0f}, .Color{1.0f}},
			{.Position{-1.0f,  1.0f, 0.0f}, .TexCoord{0.0f, 1.0f}, .Normal{0.0f, 0.0f, -1.0f}, .Color{1.0f}},
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

	}

	Mesh::~Mesh()
	{

	}


}
