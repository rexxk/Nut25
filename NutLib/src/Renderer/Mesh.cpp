#include "Renderer/Mesh.h"

#include "Renderer/OpenGLShader.h"
#include "Renderer/Renderer.h"

#include <stb_image.h>

#include <glad/glad.h>



namespace Nut
{


//	auto Mesh::Create(const std::vector<Ref<VertexBuffer>>& vertexBuffers, Ref<IndexBuffer> indexBuffer, const std::string& shaderName) -> Ref<Mesh>
//	{
//		return CreateRef<Mesh>(vertexBuffers, indexBuffer, shaderName);
//	}

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

//		m_Vertices = vertices;
//		m_Indices = indices;

//		Ref<Buffer> vertexBuffer = Nut::Buffer::Create(vertices.data(), vertices.size(), sizeof(Nut::Vertex));
//		Ref<Buffer> indexBuffer = Nut::Buffer::Create(indices.data(), indices.size(), sizeof(uint32_t));
//
//		Ref<Nut::VertexBuffer> vb = Nut::VertexBuffer::Create(vertexBuffer);
//		Ref<Nut::IndexBuffer> ib = Nut::IndexBuffer::Create(indexBuffer);
//
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

//		Ref<Buffer> vertexBuffer = Buffer::Create(vertices.data(), vertices.size(), sizeof(Vertex));
//		Ref<Buffer> indexBuffer = Buffer::Create(indices.data(), indices.size(), sizeof(uint32_t));
//
//		Ref<VertexBuffer> vb = VertexBuffer::Create(vertexBuffer);
//		Ref<IndexBuffer> ib = IndexBuffer::Create(indexBuffer);

		return CreateRef<Mesh>(vertices, indices, "Rectangle");

	}


	auto Mesh::CreatePlane(uint32_t width, uint32_t height, const std::filesystem::path& heightmap) -> Ref<Mesh>
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

		uint32_t index{ 0l };

		int32_t halfHeight = height >> 1;
		int32_t halfWidth = width >> 1;

		/*		for (auto y = -halfHeight; y < halfHeight - 1; y++)
				{
					for (auto x = -halfWidth; x < halfWidth - 1; x++)
					{
		//				auto p1 = (width * y) + x;
		//				auto p2 = (width * y) + (x + 1);
		//				auto p3 = (width * (y + 1)) + x;
		//				auto p4 = (width * (y + 1)) + (x + 1);

						{
							Vertex v{};
							v.Position = glm::vec3{ x, 0.0f, y };
							v.TexCoord = glm::vec2{ 0.0f, 0.0f };
							v.Normal = glm::vec3{ 0.0f, 1.0f, 0.0f };
							v.Color = glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f };
		//					v.Color = glm::vec4{ 0.5f, 0.5f, 0.5f, 1.0f };

							vertices.push_back(v);
						}

						{
							Vertex v{};
							v.Position = glm::vec3{ x + 1, 0.0f, y };
							v.TexCoord = glm::vec2{ 1.0f, 0.0f };
							v.Normal = glm::vec3{ 0.0f, 1.0f, 0.0f };
							v.Color = glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f };
		//					v.Color = glm::vec4{ 0.5f, 0.5f, 0.5f, 1.0f };

							vertices.push_back(v);
						}

						{
							Vertex v{};
							v.Position = glm::vec3{ x, 0.0f, y + 1 };
							v.TexCoord = glm::vec2{ 0.0f, 1.0f };
							v.Normal = glm::vec3{ 0.0f, 1.0f, 0.0f };
							v.Color = glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f };
		//					v.Color = glm::vec4{ 0.5f, 0.5f, 0.5f, 1.0f };

							vertices.push_back(v);
						}

						{
							Vertex v{};
							v.Position = glm::vec3{ x + 1, 0.0f, y + 1 };
							v.TexCoord = glm::vec2{ 1.0f, 1.0f };
							v.Normal = glm::vec3{ 0.0f, 1.0f, 0.0f };
							v.Color = glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f };
		//					v.Color = glm::vec4{ 0.5f, 0.5f, 0.5f, 1.0f };

							vertices.push_back(v);
						}

						indices.push_back(index + 0);
						indices.push_back(index + 1);
						indices.push_back(index + 2);
						indices.push_back(index + 3);
						indices.push_back(index + 2);
						indices.push_back(index + 1);

						index += 4;
					}
				}
		*/

		vertices.resize(width * height);
		size_t position = 0;

		if (heightmap.empty())
		{
			for (auto z = -halfHeight; z < halfHeight; z++)
			{
				for (auto x = -halfWidth; x < halfWidth; x++)
				{
					Vertex v{};
					v.Position = glm::vec3{ static_cast<float>(x), 0.0f, static_cast<float>(z) };
					v.TexCoord = glm::vec2{ std::abs(x % 2), std::abs(z % 2) };
					v.Normal = glm::vec3{ 0.0f, 1.0f, 0.0f };
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
			auto pixels = stbi_load(heightmap.string().c_str(), &width, &height, &bitsPerPixel, 4);

			for (auto z = -halfHeight; z < halfHeight; z++)
			{
				for (auto x = -halfWidth; x < halfWidth; x++)
				{
					Vertex v{};
					v.Position = glm::vec3{ static_cast<float>(x), 2.5f * (1 - ((pixels[(z + halfHeight) * width + (x + halfWidth)] + 1) / 255.0f)), static_cast<float>(z)};
					v.TexCoord = glm::vec2{ std::abs(x % 2), std::abs(z % 2) };
					v.Normal = glm::vec3{ 0.0f, 1.0f, 0.0f };
					v.Color = glm::vec4{ 1.0f };

					vertices[position++] = v;
				}
			}

			stbi_image_free(pixels);
		}

		indices.resize(width * height * 6);
		index = 0l;
		for (auto z = 0; z < height - 1; z++)
		{
			for (auto x = 0; x < width - 1; x++)
			{
				auto v1 = (width * z) + x;
				auto v2 = (width * z) + (x + 1);
				auto v3 = (width * (z + 1)) + x;
				auto v4 = (width * (z + 1)) + (x + 1);

				indices[index++] = v1;
				indices[index++] = v2;
				indices[index++] = v3;
				indices[index++] = v4;
				indices[index++] = v3;
				indices[index++] = v2;
			}
		}

		return CreateRef<Mesh>(vertices, indices, "Plane");
	}

//	Mesh::Mesh(const std::vector<Ref<VertexBuffer>>& vertexBuffers, Ref<IndexBuffer> indexBuffer, const std::string& shaderName)
//		: m_VertexBuffers(vertexBuffers), m_IndexBuffer(indexBuffer)
//	{
//		auto shader = ShaderLibrary::Get(shaderName);
//
//		auto& layout = shader->GetLayout();
//
//		glCreateVertexArrays(1, &m_VAO);
//
//		GLuint stride{ 0 };
//
//		for (auto i = 0; i < layout.size(); i++)
//		{
//			if (layout.find(i) == layout.end())
//				continue;
//
//			auto& layoutInfo = layout.at(i);
//
//			glEnableVertexArrayAttrib(m_VAO, i);
//
//			glVertexArrayAttribFormat(m_VAO, i, layoutInfo.Count, layoutInfo.Type, GL_FALSE, stride);
//
//			glVertexArrayAttribBinding(m_VAO, i, layoutInfo.VertexBufferPosition);
//
//			stride += layoutInfo.Size;
//		}
//
//		uint32_t i = 0;
//
//		for (auto& vertexBuffer : m_VertexBuffers)
//		{
//			glVertexArrayVertexBuffer(m_VAO, i++, vertexBuffer->Handle(), 0, sizeof(Vertex));
//		}
//
//		glVertexArrayElementBuffer(m_VAO, m_IndexBuffer->Handle());
//
//	}

	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::string& name)
		: m_Vertices(vertices), m_Indices(indices), m_Name(name)
	{

	}

	Mesh::~Mesh()
	{
//		if (m_VAO != 0)
//			glDeleteVertexArrays(1, &m_VAO);
	}

//	auto Mesh::Draw() -> void
//	{
//		glBindVertexArray(m_VAO);
//
//		glDrawElements(GL_TRIANGLES, m_IndexBuffer->IndexCount(), GL_UNSIGNED_INT, nullptr);
//	}


}
