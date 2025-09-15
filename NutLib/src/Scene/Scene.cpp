#include "Scene/Scene.h"

#include "Core/Application.h"
#include "Core/Window.h"
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
	
		Ref<Window> Window{ nullptr };
	};


	static SceneData s_SceneData;


	Scene::Scene()
	{		
		s_SceneData.Window = Application::Get().GetWindow();
		auto [windowWidth, windowHeight] = s_SceneData.Window->GetSize();

		s_SceneData.NearestSampler = Sampler::Create(GL_NEAREST);

		Nut::FramebufferSpecification framebufferSpec{};
		framebufferSpec.Width = static_cast<uint32_t>(windowWidth);
		framebufferSpec.Height = static_cast<uint32_t>(windowHeight);

		{
			Nut::FramebufferAttachment colorAttachment{};
			colorAttachment.Type = FramebufferAttachmentType::Color;
			colorAttachment.Format = GL_RGBA8;
			
			framebufferSpec.Attachments.emplace_back(colorAttachment);

			Nut::FramebufferAttachment depthAttachment{};
			depthAttachment.Type = FramebufferAttachmentType::Depth;
			depthAttachment.Format = GL_DEPTH_COMPONENT32F;

			framebufferSpec.Attachments.emplace_back(depthAttachment);
		}

		s_SceneData.FlatFramebuffer = OpenGLFramebuffer::Create(framebufferSpec);

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

			auto [windowWidth, windowHeight] = s_SceneData.Window->GetSize();
			glViewport(0, 0, windowWidth, windowHeight);

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
