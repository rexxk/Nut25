#pragma once

#include <glm/glm.hpp>


namespace Nut
{


	struct Vertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
	};


	class Renderer
	{
	public:
		static auto DrawTriangle() -> void;

	};

}
