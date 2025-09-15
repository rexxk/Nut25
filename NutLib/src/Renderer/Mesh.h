#pragma once

#include "Renderer/OpenGLBuffer.h"
#include "Renderer/OpenGLShader.h"

#include <cstdint>
#include <vector>

#include <glad/glad.h>


namespace Nut
{


	class Mesh
	{
	public:
		static auto Create(const std::vector<Ref<VertexBuffer>>& vertexBuffers, Ref<IndexBuffer> indexBuffer, const std::string& shader) -> Ref<Mesh>;
		static auto CreateRectangle(const std::string& shaderName) -> Ref<Mesh>;

		Mesh(const std::vector<Ref<VertexBuffer>>& vertexBuffers, Ref<IndexBuffer> indexBuffer, const std::string& shader);
		~Mesh();

		auto Draw() -> void;

	private:
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer{ nullptr };

		GLuint m_VAO{ 0 };

	};


}
