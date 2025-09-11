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
	};


	static SceneData s_SceneData;


	Scene::Scene()
	{
		s_SceneData.NearestSampler = Sampler::Create(GL_NEAREST);


	}


	auto Scene::Draw() -> void
	{
		OpenGLShader::ReleaseBinding();

		auto shader = ShaderLibrary::Get("FlatShader");
		shader->Bind();
		
		glBindSampler(0, s_SceneData.NearestSampler->ID());

		shader->SetUniform("u_Texture", 0);

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
