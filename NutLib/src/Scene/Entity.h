#pragma once


#include "Core/Base.h"


namespace Nut
{


	class Mesh;

	class Entity
	{
	public:
		static auto Create(Ref<Mesh> mesh) -> Ref<Entity>;

		Entity(Ref<Mesh> mesh);

	private:
		Ref<Mesh> m_Mesh;

	};


}
