#include "Scene/Scene.h"

#include "Core/Application.h"
#include "Core/UUID.h"
#include "Core/Window.h"
#include "Renderer/Mesh.h"
#include "Renderer/OpenGLBuffer.h"
#include "Renderer/OpenGLFramebuffer.h"
#include "Renderer/OpenGLShader.h"
#include "Renderer/Texture.h"
#include "Scene/Camera.h"
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

		Ref<Camera> SceneCamera{ nullptr };
		Ref<UniformBuffer> ViewProjectionUniformBuffer{ nullptr };

		Ref<Window> Window{ nullptr };
	};

	static SceneData s_SceneData;

	struct SceneBuffers
	{
		Ref<Buffer> ViewProjectionBuffer{ nullptr };
	};

	static SceneBuffers s_SceneBuffers;

	struct SceneDrawData
	{
		std::unordered_map<UUID, std::vector<glm::mat4>> InstanceMap;
	};

	static SceneDrawData s_SceneDrawData;

	struct ViewProjectionUniform
	{
		glm::mat4 ViewProjectionMatrix;
	};

	static ViewProjectionUniform s_ViewProjectionUniform;

	auto Camera::Create(const glm::vec3& position, const glm::vec3& rotation, int32_t canvasWidth, int32_t canvasHeight) -> Ref<Camera>
	{
		return CreateRef<Camera>(position, rotation, canvasWidth, canvasHeight);
	}


	Scene::Scene()
	{		
		s_SceneData.Window = Application::Get().GetWindow();
		auto [windowWidth, windowHeight] = s_SceneData.Window->GetSize();

		s_SceneData.SceneCamera = Camera::Create(glm::vec3{ 3.0f, 3.0f, -5.0f }, glm::vec3{ 0.0f }, windowWidth, windowHeight);

		s_ViewProjectionUniform.ViewProjectionMatrix = s_SceneData.SceneCamera->ViewProjectionMatrix();
		s_SceneData.ViewProjectionUniformBuffer = UniformBuffer::Create(&s_ViewProjectionUniform, sizeof(ViewProjectionUniform));

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

//		s_SceneData.DrawRectangle = Mesh::CreateRectangle("FlatShader");
		s_SceneData.DrawRectangle = Mesh::CreateRectangle();

	}

	auto Scene::Update(double ts) -> void
	{
		s_ViewProjectionUniform.ViewProjectionMatrix = s_SceneData.SceneCamera->ViewProjectionMatrix();
		s_SceneData.ViewProjectionUniformBuffer->SetData(&s_ViewProjectionUniform, sizeof(ViewProjectionUniform));


	}

	auto Scene::Draw() -> void
	{
		s_SceneDrawData.InstanceMap.clear();

		for (auto& entity : s_SceneData.Entities)
		{
			if (entity->ModelID() != 0)
				s_SceneDrawData.InstanceMap[entity->ModelID()].push_back(entity->GetTransform().TransformMatrix);
		}


		OpenGLShader::ReleaseBinding();

		auto [windowWidth, windowHeight] = s_SceneData.Window->GetSize();
		glViewport(0, 0, windowWidth, windowHeight);

		{
			auto shader = ShaderLibrary::Get("FlatShader");
			shader->Bind();

			glBindSampler(0, s_SceneData.NearestSampler->ID());

			glBindFramebuffer(GL_FRAMEBUFFER, s_SceneData.FlatFramebuffer->ID());

			s_SceneData.FlatFramebuffer->Clear();

			glBindBufferRange(GL_UNIFORM_BUFFER, 0, s_SceneData.ViewProjectionUniformBuffer->Handle(), 0, sizeof(ViewProjectionUniform));
//			shader->SetUniform("u_ViewProjection", s_SceneData.SceneCamera->ViewProjectionMatrix());
			shader->SetUniform("u_Texture", 0);


			for (auto& [modelID, transformMatrices] : s_SceneDrawData.InstanceMap)
			{
				Renderer::DrawInstanced(modelID, transformMatrices, shader->GetLayout());
			}

//			for (auto& entity : s_SceneData.Entities)
//			{
//				entity->Draw();
//			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		{
			ShaderLibrary::Get("CompositionShader")->Bind();

			s_SceneData.FlatFramebuffer->GetColorAttachment()->BindToSlot(0);

			Renderer::DrawMesh(s_SceneData.DrawRectangle);
//			s_SceneData.DrawRectangle->Draw();
		}



	}

	auto Scene::AddEntity(Ref<Entity> entity) -> void
	{
		s_SceneData.Entities.emplace_back(entity);

	}

}
