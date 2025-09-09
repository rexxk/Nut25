#include "Scene/Scene.h"

#include "Renderer/OpenGLShader.h"
#include "Renderer/Texture.h"
#include "Scene/Entity.h"

#include <vector>


namespace Nut
{


	struct SceneData
	{
		std::vector<Ref<Entity>> Entities;

		Ref<Sampler> NearestSampler{ nullptr };

		Ref<Texture2D> RedTexture{ nullptr };
	};


	static SceneData s_SceneData;


	Scene::Scene()
	{
		s_SceneData.NearestSampler = Sampler::Create(GL_NEAREST);

		TextureSpecification texSpec{};
		texSpec.UnitTexture = true;
		texSpec.Color = glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f };
		s_SceneData.RedTexture = Texture2D::Create(texSpec);

	}


	auto Scene::Draw() -> void
	{
		OpenGLShader::ReleaseBinding();

		auto shader = ShaderLibrary::Get("FlatShader");
		shader->Bind();

		glBindSampler(0, s_SceneData.NearestSampler->ID());
		
		shader->SetUniform("u_Texture", 0);

		s_SceneData.RedTexture->BindToSlot(0);

		for (auto& entity : s_SceneData.Entities)
		{
			entity->Draw();
		}
	}

	auto Scene::AddEntity(Ref<Entity> entity) -> void
	{
		s_SceneData.Entities.emplace_back(entity);

	}

}
