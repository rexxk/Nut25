#include <print>

#include "EntryPoint.h"
#include "NutLib.h"

#include <print>
#include <vector>

#include <glm/gtc/constants.hpp>


class SandboxLayer : public Nut::Layer
{
public:
	SandboxLayer(const std::string& debugName)
		: Layer(debugName)
	{

	}

	virtual auto OnAttach() -> void override
	{
		std::println("Attaching {} layer", m_DebugName);

		m_RendererContext = Nut::Application::Get().GetWindow()->GetRendererContext();


//		auto mesh = Nut::Mesh::CreateTriangle("FlatShader");
//		auto mesh = Nut::Mesh::CreateTriangle();
//		auto meshID = Nut::AssetManager::AddMesh(Nut::Mesh::CreateTriangle());
		auto meshID = Nut::AssetManager::AddMesh(Nut::Mesh::CreateRectangle());


		Nut::TextureSpecification texSpec{};
		texSpec.Filepath = "Assets/Textures/texture.png";
//		texSpec.Filepath = "C:/Programming/Private/Nut25/Sandbox/Assets/Textures/texture.png";
//		texSpec.Format = GL_RGBA;
//		texSpec.UnitTexture = true;
//		texSpec.Color = glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f };
		

		Ref<Nut::Texture2D> texture = Nut::Texture2D::Create(texSpec);

		auto triangleModelID = Nut::AssetManager::AddModel(Nut::Model::Create({ meshID }, { {Nut::TextureType::Albedo, texture} }));

		m_TestEntity = Nut::Entity::Create(triangleModelID);
		m_Entity2 = Nut::Entity::Create(triangleModelID);
		m_Entity3 = Nut::Entity::Create(triangleModelID);

		m_Entity2->GetTransform().Position = glm::vec3{ 5.0f, 0.0f, 0.0f };
		m_Entity3->GetTransform().Position = glm::vec3{ -5.0f, 0.0f, 0.0f };

		m_Scene.AddEntity(m_TestEntity);
		m_Scene.AddEntity(m_Entity2);
		m_Scene.AddEntity(m_Entity3);
	}

	virtual auto OnDetach() -> void override
	{
		std::println("Detaching {} layer", m_DebugName);
	}

	virtual auto OnUpdate(double timestep) -> void override
	{
		m_RendererContext->BeginScene();

		auto elapsedTime = static_cast<float>(m_UpdateTimer.ElapsedTime() / 1000.0f);
		constexpr auto twoPi = glm::two_pi<float>();

		{
			auto& transform = m_TestEntity->GetTransform();

			transform.Position.x = 1.5f * std::sinf(twoPi * 0.15f * elapsedTime);
			transform.Position.y = 2.0f * std::cosf(twoPi * 0.35f * elapsedTime);

			transform.Rotation.z = 3.0f * std::sinf(twoPi * 0.1f * elapsedTime);

			transform.Scale = glm::vec3{ std::cosf(twoPi * 0.3f * elapsedTime) + 1.2f };
		}

		{
			auto& transform = m_Entity2->GetTransform();
			transform.Position.y = 2.5f * std::cosf(twoPi * 0.25f * elapsedTime);

			transform.Rotation.y = 2.0f * std::sinf(twoPi * 0.05f * elapsedTime);
		}
	
		{
			auto& transform = m_Entity3->GetTransform();
			transform.Position.y = 2.5f * std::sinf(twoPi * 0.1f * elapsedTime);

			transform.Rotation.x = 5.0f * std::cosf(twoPi * 0.075 * elapsedTime);
		}

		m_Scene.Update(timestep);
		m_Scene.Draw();
	}


private:
	Ref<Nut::RendererContext> m_RendererContext;

	Ref<Nut::Buffer> m_VertexData{ nullptr };
	Ref<Nut::Buffer> m_IndexData{ nullptr };

	Ref<Nut::Entity> m_TestEntity{ nullptr };
	Ref<Nut::Entity> m_Entity2{ nullptr };
	Ref<Nut::Entity> m_Entity3{ nullptr };

	Nut::Timer m_UpdateTimer{};

	Nut::Scene m_Scene;
};



class SandboxApp : public Nut::Application
{
public:
	SandboxApp(const Nut::ApplicationSettings& settings)
		: Nut::Application(settings)
	{
		AttachLayer(CreateRef<SandboxLayer>("Sandbox"));
	}

};


Ref<Nut::Application> CreateApplication()
{
	Nut::ApplicationSettings settings{ .Width = 1280, .Height = 720, .VSync{true}, .Fullscreen{false} };

	return CreateRef<SandboxApp>(settings);
}
