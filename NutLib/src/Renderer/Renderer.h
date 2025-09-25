#pragma once

#include "Core/Base.h"
#include "Scene/Entity.h"

#include <glm/glm.hpp>


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

	class Renderer
	{
	public:
		static auto DrawTriangle() -> void;

		static auto DrawInstanced(Ref<Entity> entity, const std::vector<glm::mat4>& transformMatrices) -> void;

		static auto DrawMesh(Ref<Mesh> mesh) -> void;
	};

}
