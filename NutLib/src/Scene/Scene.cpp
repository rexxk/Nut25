#include "Scene/Scene.h"

#include "Renderer/Mesh.h"
#include "Renderer/OpenGLFramebuffer.h"
#include "Renderer/OpenGLShader.h"
#include "Renderer/Texture.h"
#include "Scene/Entity.h"

#include <vector>




namespace Nut
{


	struct SceneData
	{
		std::vector<Ref<Entity>> Entities;

		Ref<Mesh> DrawRectangle{ nullptr };

		Ref<Sampler> NearestSampler{ nullptr };

		Ref<OpenGLFramebuffer> FlatFramebuffer{ nullptr };
	};


	static SceneData s_SceneData;


	Scene::Scene()
	{		
		s_SceneData.NearestSampler = Sampler::Create(GL_NEAREST);

		Nut::FramebufferSpecification framebufferSpec{};
		framebufferSpec.Width = 256;
		framebufferSpec.Height = 256;

		{
			Nut::FramebufferAttachment colorAttachment{};
			colorAttachment.Type = Nut::FramebufferAttachmentType::Color;
			colorAttachment.Format = GL_RGBA;

			framebufferSpec.Attachments.emplace_back(colorAttachment);
		}

		s_SceneData.FlatFramebuffer = Nut::OpenGLFramebuffer::Create(framebufferSpec);

		s_SceneData.DrawRectangle = Mesh::CreateRectangle("FlatShader");

	}


	auto Scene::Draw() -> void
	{
		OpenGLShader::ReleaseBinding();

		{
			auto shader = ShaderLibrary::Get("FlatShader");
			shader->Bind();

			glBindSampler(0, s_SceneData.NearestSampler->ID());

			glBindFramebuffer(GL_FRAMEBUFFER, s_SceneData.FlatFramebuffer->ID());

			glViewport(0, 0, 256, 256);

			s_SceneData.FlatFramebuffer->Clear();

//			glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
//			glClear(GL_COLOR_BUFFER_BIT);


			shader->SetUniform("u_Texture", 0);

			for (auto& entity : s_SceneData.Entities)
			{
				entity->Draw();
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}


		{
			s_SceneData.FlatFramebuffer->GetColorAttachment()->BindToSlot(0);

			s_SceneData.DrawRectangle->Draw();
		}


	}

	auto Scene::AddEntity(Ref<Entity> entity) -> void
	{
		s_SceneData.Entities.emplace_back(entity);

	}

}
