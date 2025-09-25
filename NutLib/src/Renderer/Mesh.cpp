#include "Renderer/Mesh.h"

#include "Renderer/OpenGLShader.h"
#include "Renderer/Renderer.h"

#include <glad/glad.h>



namespace Nut
{


//	auto Mesh::Create(const std::vector<Ref<VertexBuffer>>& vertexBuffers, Ref<IndexBuffer> indexBuffer, const std::string& shaderName) -> Ref<Mesh>
//	{
//		return CreateRef<Mesh>(vertexBuffers, indexBuffer, shaderName);
//	}

	auto Mesh::Create(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) -> Ref<Mesh>
	{
		return CreateRef<Mesh>(vertices, indices);
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
		return CreateRef<Mesh>(vertices, indices);
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

		return CreateRef<Mesh>(vertices, indices);

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

	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
		: m_Vertices(vertices), m_Indices(indices)
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
