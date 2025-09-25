#pragma once

#include "Core/Base.h"
#include "Core/UUID.h"

//#include "Renderer/OpenGLBuffer.h"
//#include "Renderer/OpenGLShader.h"
#include "Renderer/Renderer.h"

#include <cstdint>
#include <vector>

#include <glad/glad.h>


namespace Nut
{



	class Mesh
	{
	public:
		static auto Create(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) -> Ref<Mesh>;
//		static auto Create(const std::vector<Ref<VertexBuffer>>& vertexBuffers, Ref<IndexBuffer> indexBuffer, const std::string& shader) -> Ref<Mesh>;
		static auto CreateTriangle() -> Ref<Mesh>;
		static auto CreateRectangle() -> Ref<Mesh>;
//		static auto CreateTriangle(const std::string& shaderName) -> Ref<Mesh>;
//		static auto CreateRectangle(const std::string& shaderName) -> Ref<Mesh>;

//		Mesh(const std::vector<Ref<VertexBuffer>>& vertexBuffers, Ref<IndexBuffer> indexBuffer, const std::string& shader);
		Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
		~Mesh();

		auto GetVertices() const -> const std::vector<Vertex>& { return m_Vertices; }
		auto GetIndices() const -> const std::vector<uint32_t>& { return m_Indices; }

		auto MeshID() const -> const UUID { return m_MeshID; }

//		auto Draw() -> void;

	private:
//		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
//		Ref<IndexBuffer> m_IndexBuffer{ nullptr };

//		GLuint m_VAO{ 0 };

		std::vector<Vertex> m_Vertices{};
		std::vector<uint32_t> m_Indices{};

		UUID m_MeshID{};

	};


}
