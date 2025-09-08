#include "Scene/Scene.h"

#include "Renderer/OpenGLShader.h"
#include "Scene/Entity.h"

#include <vector>


namespace Nut
{


	struct SceneData
	{
		std::vector<Ref<Entity>> Entities;
	};


	static SceneData s_SceneData;


	Scene::Scene()
	{

	}


	auto Scene::Draw() -> void
	{
		OpenGLShader::ReleaseBinding();

		ShaderLibrary::Get("FlatShader")->Bind();

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
