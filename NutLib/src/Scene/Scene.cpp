#include "Scene/Scene.h"

#include "Assets/AssetManager.h"
#include "Core/Application.h"
#include "Core/UUID.h"
#include "Core/Window.h"
#include "Renderer/Mesh.h"
#include "Renderer/OpenGLBuffer.h"
#include "Renderer/OpenGLFramebuffer.h"
#include "Renderer/OpenGLShader.h"
#include "Renderer/TerrainMesh.h"
#include "Renderer/Texture.h"
#include "Scene/Camera.h"
#include "Scene/CameraController.h"
#include "Scene/Entity.h"
#include "Scene/Model.h"

#include "imgui.h"

#include <vector>

#include <glm/gtc/type_ptr.hpp>



namespace Nut
{

	enum class TextureSlot : uint32_t
	{
		Albedo = 0,
		Normal,
		Metalness,
		Roughness,
		AmbientOcclusion,
	};

	struct SceneData
	{
		std::vector<Ref<Entity>> Entities;

		Ref<Mesh> DrawRectangle{ nullptr };
		Ref<Model> TerrainModel{ nullptr };

		Ref<Sampler> NearestSampler{ nullptr };
		Ref<Sampler> LinearSampler{ nullptr };

		Ref<OpenGLFramebuffer> FlatFramebuffer{ nullptr };

		Ref<Camera> SceneCamera{ nullptr };
		Ref<CameraController> CameraController{ nullptr };
		Ref<UniformBuffer> ViewProjectionUniformBuffer{ nullptr };
		Ref<UniformBuffer> DirectionalLightUniformBuffer{ nullptr };

		Ref<Window> Window{ nullptr };
	};

	static SceneData s_SceneData;

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

	struct DirectionalLight
	{
		glm::vec3 Direction;
		float Padding;
		glm::vec3 Radiance;
		float Padding2;
	};

	static DirectionalLight s_DirectionalLightUniform;

	auto Camera::Create(const glm::vec3& position, const glm::vec3& rotation, int32_t canvasWidth, int32_t canvasHeight) -> Ref<Camera>
	{
		return CreateRef<Camera>(position, rotation, canvasWidth, canvasHeight);
	}

	static HeightmapSpecification s_HeightmapSpecification{ .NoiseDivider1{14.0f}, .NoiseDivider2{28.0f}, .NoiseDivider3{19.0f}, .Divider{16.0f} };

	Scene::Scene()
	{		
		s_SceneData.Window = Application::Get().GetWindow();
		auto [windowWidth, windowHeight] = s_SceneData.Window->GetSize();

		s_SceneData.SceneCamera = Camera::Create(glm::vec3{ 3.0f, 3.0f, -5.0f }, glm::vec3{ 0.0f }, windowWidth, windowHeight);
		s_SceneData.CameraController = CreateRef<CameraController>(s_SceneData.SceneCamera);

		s_ViewProjectionUniform.ViewProjectionMatrix = s_SceneData.SceneCamera->ViewProjectionMatrix();
		s_SceneData.ViewProjectionUniformBuffer = UniformBuffer::Create(&s_ViewProjectionUniform, sizeof(ViewProjectionUniform));

		s_DirectionalLightUniform = DirectionalLight{ .Direction{-0.3f, 0.5f, 0.75f}, .Radiance{1.0f} };
		s_SceneData.DirectionalLightUniformBuffer = UniformBuffer::Create(&s_DirectionalLightUniform, sizeof(DirectionalLight));

		s_SceneData.NearestSampler = Sampler::Create(SamplerFilterType::Nearest);
		s_SceneData.LinearSampler = Sampler::Create(SamplerFilterType::Linear);

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
		s_SceneData.CameraController->Update(ts);

		s_ViewProjectionUniform.ViewProjectionMatrix = s_SceneData.SceneCamera->ViewProjectionMatrix();
		s_SceneData.ViewProjectionUniformBuffer->SetData(&s_ViewProjectionUniform, sizeof(ViewProjectionUniform));

		s_SceneData.DirectionalLightUniformBuffer->SetData(&s_DirectionalLightUniform, sizeof(DirectionalLight));


		{
			ImGui::Begin("Directional Light");

			ImGui::Text("Direction");
			ImGui::DragFloat3("##Direction", glm::value_ptr(s_DirectionalLightUniform.Direction), 0.01f, -1.0f, 1.0f);
			ImGui::Separator();
			ImGui::Text("Radiance");
			ImGui::ColorPicker3("##Radiance", glm::value_ptr(s_DirectionalLightUniform.Radiance));

			ImGui::End();
		}

		if (s_SceneData.TerrainModel != nullptr)
		{
			ImGui::Begin("Heightmap");

			ImGui::Text("Divider 1"); ImGui::SameLine(); ImGui::DragFloat("##div1", &s_HeightmapSpecification.NoiseDivider1, 0.1f, 0.1f, 100.0f);
			ImGui::Text("Divider 2"); ImGui::SameLine(); ImGui::DragFloat("##div2", &s_HeightmapSpecification.NoiseDivider2, 0.1f, 0.1f, 100.0f);
			ImGui::Text("Divider 3"); ImGui::SameLine(); ImGui::DragFloat("##div3", &s_HeightmapSpecification.NoiseDivider3, 0.1f, 0.1f, 100.0f);
			ImGui::Text("Smoothness"); ImGui::SameLine(); ImGui::DragFloat("##smoothness", &s_HeightmapSpecification.Divider, 0.1f, 0.1f, 100.0f);
			ImGui::Text("Texture multiplier"); ImGui::SameLine(); ImGui::DragFloat("##textureMultiplier", &s_HeightmapSpecification.TextureMultiplier, 1.0f, 1.0f, 128.0f);

			if (ImGui::Button("Generate"))
			{
				std::dynamic_pointer_cast<TerrainMesh>(AssetManager::GetMesh(s_SceneData.TerrainModel->MeshIDs()[0]))->UpdateHeightmap(s_HeightmapSpecification);
				Renderer::UpdateModel(s_SceneData.TerrainModel);
			}

			ImGui::End();
		}
	}

	auto Scene::Draw() -> void
	{
		s_SceneDrawData.InstanceMap.clear();

		for (auto& entity : s_SceneData.Entities)
		{
			if (entity->ModelID() != 0)
			{
				entity->CalculateTransformMatrix();
			}	s_SceneDrawData.InstanceMap[entity->ModelID()].push_back(entity->GetTransform().TransformMatrix);
		}


		OpenGLShader::ReleaseBinding();

		auto [windowWidth, windowHeight] = s_SceneData.Window->GetSize();
		glViewport(0, 0, windowWidth, windowHeight);

//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//		glEnable(GL_CULL_FACE);
//		glCullFace(GL_FRONT);

		{
			auto shader = ShaderLibrary::Get("FlatShader");
			shader->Bind();

			glBindSampler(0, s_SceneData.NearestSampler->ID());
//			glBindSampler(0, s_SceneData.LinearSampler->ID());

			glBindFramebuffer(GL_FRAMEBUFFER, s_SceneData.FlatFramebuffer->ID());

			s_SceneData.FlatFramebuffer->Clear();

			glBindBufferRange(GL_UNIFORM_BUFFER, 0, s_SceneData.ViewProjectionUniformBuffer->Handle(), 0, sizeof(ViewProjectionUniform));
			glBindBufferRange(GL_UNIFORM_BUFFER, 1, s_SceneData.DirectionalLightUniformBuffer->Handle(), 0, sizeof(DirectionalLight));
//			shader->SetUniform("u_ViewProjection", s_SceneData.SceneCamera->ViewProjectionMatrix());

			auto albedoSlot = std::underlying_type<TextureSlot>::type(TextureSlot::Albedo);
			auto normalSlot = std::underlying_type<TextureSlot>::type(TextureSlot::Normal);
			auto metalnessSlot = std::underlying_type<TextureSlot>::type(TextureSlot::Metalness);
			auto roughnessSlot = std::underlying_type<TextureSlot>::type(TextureSlot::Roughness);
			auto ambientOcclusionSlot = std::underlying_type<TextureSlot>::type(TextureSlot::AmbientOcclusion);

			shader->SetUniform("u_Texture", albedoSlot);

			for (auto& [modelID, transformMatrices] : s_SceneDrawData.InstanceMap)
			{
				auto& textures = AssetManager::GetModel(modelID)->GetTextures();

				if (textures.contains(TextureType::Albedo))
				{
					textures.at(TextureType::Albedo)->BindToSlot(albedoSlot);
				}

				Renderer::DrawInstanced(modelID, transformMatrices, shader->GetLayout());
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

//		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_CULL_FACE);

		{
			auto shader = ShaderLibrary::Get("CompositionShader");
			shader->Bind();

			s_SceneData.FlatFramebuffer->GetColorAttachment()->BindToSlot(0);

			Renderer::DrawMesh(s_SceneData.DrawRectangle, shader->GetLayout());
		}



	}

	auto Scene::AddEntity(Ref<Entity> entity) -> void
	{
		s_SceneData.Entities.emplace_back(entity);

	}

	auto Scene::SetTerrainModel(Ref<Model> terrainModel) -> void
	{
		s_SceneData.TerrainModel = terrainModel;
	}

}
