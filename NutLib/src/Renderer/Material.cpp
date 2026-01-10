#include "Renderer/Material.h"



namespace Nut
{

	auto Material::Create(Ref<Program> shader, const MaterialSpecification& specification) -> Scope<Material>
	{
		return CreateScope<Material>(shader, specification);
	}

	Material::Material(Ref<Program> shader, const MaterialSpecification& specification)
		: m_Shader(shader), m_Specification(specification)
	{
		
	}

}
