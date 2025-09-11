#pragma once


#include "Core/Base.h"
#include "Renderer/Texture.h"


namespace Nut
{


	class Mesh;

	class Entity
	{
	public:
		static auto Create(Ref<Mesh> mesh, Ref<Texture2D> textuer) -> Ref<Entity>;

		Entity(Ref<Mesh> mesh, Ref<Texture2D> teture);

		auto Draw() -> void;

	private:
		Ref<Mesh> m_Mesh{ nullptr };

		Ref<Texture2D> m_Texture{ nullptr };
	};


}
