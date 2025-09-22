#pragma once


#include "Core/Base.h"
#include "Renderer/Texture.h"

#include <glm/glm.hpp>


namespace Nut
{


	struct EntityTransform
	{
		glm::vec3 Position{ 0.0f };
		glm::vec3 Rotation{ 0.0f };
		glm::vec3 Scale{ 1.0f };

		glm::mat4 TransformMatrix{ 1.0f };
	};

	class Mesh;

	class Entity
	{
	public:
		static auto Create(Ref<Mesh> mesh, Ref<Texture2D> textuer) -> Ref<Entity>;

		Entity(Ref<Mesh> mesh, Ref<Texture2D> teture);

		auto GetTransform() -> EntityTransform& { return m_Transform; }

		auto Draw() -> void;

	private:
		Ref<Mesh> m_Mesh{ nullptr };

		Ref<Texture2D> m_Texture{ nullptr };

		EntityTransform m_Transform{};
	};


}
