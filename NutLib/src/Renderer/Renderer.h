#pragma once

#include "Core/Base.h"
#include "Core/UUID.h"

#include <glm/glm.hpp>

#include <glad/glad.h>


namespace Nut
{


	struct Vertex
	{
		glm::vec3 Position;
		glm::vec2 TexCoord;
		glm::vec3 Normal;
		glm::vec4 Color;
	};


	class Mesh;
	struct ShaderLayoutInfo;



	class Renderer
	{
	public:
		static auto DrawTriangle() -> void;

		static auto DrawInstanced(UUID modelID, const std::vector<glm::mat4>& transformMatrices, const std::unordered_map<GLint, ShaderLayoutInfo>& shaderLayout) -> void;
		static auto DrawMesh(Ref<Mesh> mesh, const std::unordered_map<GLint, ShaderLayoutInfo>& shaderLayout) -> void;

	};

}
