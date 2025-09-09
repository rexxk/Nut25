#include "Renderer/Mesh.h"

#include "Renderer/OpenGLShader.h"
#include "Renderer/Renderer.h"

#include <glad/glad.h>



namespace Nut
{


	auto Mesh::Create(const std::vector<Ref<VertexBuffer>>& vertexBuffers, Ref<IndexBuffer> indexBuffer, const std::string& shaderName) -> Ref<Mesh>
	{
		return CreateRef<Mesh>(vertexBuffers, indexBuffer, shaderName);
	}


	Mesh::Mesh(const std::vector<Ref<VertexBuffer>>& vertexBuffers, Ref<IndexBuffer> indexBuffer, const std::string& shaderName)
		: m_VertexBuffers(vertexBuffers), m_IndexBuffer(indexBuffer)
	{
		auto shader = ShaderLibrary::Get(shaderName);

		auto& layout = shader->GetLayout();

		glCreateVertexArrays(1, &m_VAO);

		GLuint stride{ 0 };

		for (auto i = 0; i < layout.size(); i++)
		{
			if (layout.find(i) == layout.end())
				continue;

			auto& layoutInfo = layout.at(i);

			glEnableVertexArrayAttrib(m_VAO, i);

			glVertexArrayAttribFormat(m_VAO, i, layoutInfo.Count, layoutInfo.Type, GL_FALSE, stride);

			glVertexArrayAttribBinding(m_VAO, i, 0);

			stride += layoutInfo.Size;
		}

		uint32_t i = 0;

		for (auto& vertexBuffer : m_VertexBuffers)
		{
			glVertexArrayVertexBuffer(m_VAO, i++, vertexBuffer->Handle(), 0, sizeof(Vertex));
		}

		glVertexArrayElementBuffer(m_VAO, m_IndexBuffer->Handle());

	}

	Mesh::~Mesh()
	{
		if (m_VAO != 0)
			glDeleteVertexArrays(1, &m_VAO);
	}

	auto Mesh::Draw() -> void
	{
		glBindVertexArray(m_VAO);

		glDrawElements(GL_TRIANGLES, m_IndexBuffer->IndexCount(), GL_UNSIGNED_INT, nullptr);
	}


}
