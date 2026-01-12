#include "Renderer/Material.h"



namespace Nut
{

	auto Material::Create(Ref<Program> shader, const MaterialSpecification& specification) -> Material
	{
		return Material{ shader, specification };
	}

	Material::Material(Ref<Program> shader, const MaterialSpecification& specification)
		: m_Shader(shader), m_Specification(specification)
	{
		
	}

}
