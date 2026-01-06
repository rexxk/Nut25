#include <print>

#include "EntryPoint.h"
#include "NutLib.h"

#include <print>
#include <vector>

#include <glm/gtc/constants.hpp>

#include <imgui.h>



class SandboxLayer : public Nut::Layer
{
public:
	SandboxLayer(const std::string& debugName)
		: Layer(debugName)
	{

	}

	virtual auto OnAttach() -> void override
	{
		LOG_CORE_TRACE("Attaching layer: {}", m_DebugName);

		m_RendererContext = Nut::Application::Get().GetWindow()->GetRendererContext();
		ASSERT(m_RendererContext, "Application: Could not create renderer context");

//		auto mesh = Nut::Mesh::CreateTriangle("FlatShader");
//		auto mesh = Nut::Mesh::CreateTriangle();
//		auto meshID = Nut::AssetManager::AddMesh(Nut::Mesh::CreateTriangle());
//		auto meshID = Nut::AssetManager::AddMesh(Nut::Mesh::CreateRectangle());
		auto meshID = Nut::AssetManager<Scope<Nut::Mesh>>::Add("Mesh_Rectangle", std::move(Nut::Mesh::CreateRectangle()));

		{
			Nut::HeightmapSpecification heightmapSpecification{};

			heightmapSpecification.NoiseDivider1 = 14.0f;
			heightmapSpecification.NoiseDivider2 = 28.0f;
			heightmapSpecification.NoiseDivider3 = 19.0f;
			heightmapSpecification.Divider = 16.0f;

			//		heightmapSpecification.UseNoise = false;
			//		heightmapSpecification.Filepath = "Assets/Textures/terrain.png";

			Nut::AssetManager<Scope<Nut::Mesh>>::Add("Mesh_Terrain", std::move(Nut::TerrainMesh::Create(256u, 256u, heightmapSpecification)));
			//		auto terrainID = Nut::AssetManager<Ref<Nut::Mesh>>::Add(Nut::TerrainMesh::Create(256u, 256u, heightmapSpecification));
			//		auto terrainID = Nut::AssetManager::AddMesh(Nut::TerrainMesh::Create(16u, 16u, heightmapSpecification));
		}

		Nut::AssetManager<Scope<Nut::Texture2D>>::Add("Texture_Logo", std::move(Nut::Texture2D::Create({ .Filepath = "Assets/Textures/texture.png", .Format = GL_RGBA })));
		Nut::AssetManager<Scope<Nut::Texture2D>>::Add("Texture_Grass", std::move(Nut::Texture2D::Create({ .Filepath = "Assets/Textures/grass.jpg", .Format = GL_RGBA })));

		auto triangleModelID = Nut::AssetManager<Scope<Nut::Model>>::Add("Model_Rectangle", std::move(Nut::Model::Create({meshID}, { {Nut::TextureType::Albedo, Nut::AssetManager<Scope<Nut::Texture2D>>::Get("Texture_Logo")}})));
		auto terrainModelID = Nut::AssetManager<Scope<Nut::Model>>::Add("Model_Terrain", std::move(Nut::Model::Create({ Nut::AssetManager<Scope<Nut::Mesh>>::Get("Mesh_Terrain")->ID()}, {{Nut::TextureType::Albedo, Nut::AssetManager<Scope<Nut::Texture2D>>::Get("Texture_Grass")}})));

		m_TestEntity = Nut::Entity::Create(triangleModelID, "TestEntity");
		m_TestEntity->AddComponent<Nut::MeshComponent>("Mesh_Rectangle", Nut::TransformComponent{});

		m_Entity2 = Nut::Entity::Create(triangleModelID, "Entity2");
		m_Entity2->AddComponent<Nut::MeshComponent>("Mesh_Rectangle", Nut::TransformComponent{});

		m_Entity3 = Nut::Entity::Create(triangleModelID, "Entity3");
		m_Entity3->AddComponent<Nut::MeshComponent>("Mesh_Rectangle", Nut::TransformComponent{});

		m_Terrain = Nut::Entity::Create(terrainModelID, "Terrain");

		Nut::TransformComponent transform{};
		m_TestEntity->AddComponent<Nut::TransformComponent>(transform);

		transform.Position = glm::vec3{ 5.0f, 0.0f, 0.0f };
		m_Entity2->AddComponent<Nut::TransformComponent>(transform);

		transform.Position = glm::vec3{ -5.0f, 0.0f, 0.0f };
		m_Entity3->AddComponent<Nut::TransformComponent>(transform);


		m_Scene.AddEntity(m_TestEntity);
		m_Scene.AddEntity(m_Entity2);
		m_Scene.AddEntity(m_Entity3);

//		m_Scene.SetTerrainModel(Nut::AssetManager::GetModel(terrainModelID));

		transform.Position = glm::vec3{ 0.0f, -2.0f, 0.0f };
		m_Terrain->AddComponent<Nut::TransformComponent>(transform);
//		m_Terrain->GetTransform().Position = glm::vec3{ 0.0f, -2.0f, 0.0f };

		m_Scene.SetTerrainEntity(m_Terrain);

//		Nut::PerlinNoise noise{};
	}

	virtual auto OnDetach() -> void override
	{
		LOG_CORE_TRACE("Detaching layer: {}", m_DebugName);
	}

	virtual auto OnUpdate(double timestep) -> void override
	{
		m_RendererContext->BeginScene();

		auto elapsedTime = static_cast<float>(m_UpdateTimer.ElapsedTime() / 1000.0f);
		constexpr auto twoPi = glm::two_pi<float>();

		{
//			auto& transform = m_TestEntity->GetTransform();
			auto& transform = m_TestEntity->GetComponent<Nut::TransformComponent>();

			transform.Position.x = 1.5f * std::sinf(twoPi * 0.15f * elapsedTime);
			transform.Position.y = 2.0f * std::cosf(twoPi * 0.35f * elapsedTime);

			transform.Rotation.z = 3.0f * std::sinf(twoPi * 0.1f * elapsedTime);

			transform.Scale = glm::vec3{ std::cosf(twoPi * 0.3f * elapsedTime) + 1.2f };
		}

		{
//			auto& transform = m_Entity2->GetTransform();
			auto& transform = m_Entity2->GetComponent<Nut::TransformComponent>();
			transform.Position.y = 2.5f * std::cosf(twoPi * 0.25f * elapsedTime);

			transform.Rotation.y = 2.0f * std::sinf(twoPi * 0.05f * elapsedTime);
		}
	
		{
//			auto& transform = m_Entity3->GetTransform();
			auto& transform = m_Entity3->GetComponent<Nut::TransformComponent>();
			transform.Position.y = 2.5f * std::sinf(twoPi * 0.1f * elapsedTime);

			transform.Rotation.x = 5.0f * std::cosf(twoPi * 0.075f * elapsedTime);
		}

		{
//			auto& transform = m_Terrain->GetTransform();
			auto& transform = m_Terrain->GetComponent<Nut::TransformComponent>();
			transform.Position.x = 10.0f * std::sinf(twoPi * 0.1f * elapsedTime);
			transform.Position.y = 3 * std::cosf(twoPi * 0.05f * elapsedTime) - 15.0f;

			transform.Rotation.y = elapsedTime * 0.1f;
		}

		m_Scene.Update(timestep);
		m_Scene.Draw();

		ImGui::Begin("Statistics");

		ImGui::Text("ImGui controls");

		ImGui::End();

	}


private:
	Ref<Nut::RendererContext> m_RendererContext;

	Ref<Nut::Buffer> m_VertexData{ nullptr };
	Ref<Nut::Buffer> m_IndexData{ nullptr };

	Ref<Nut::Entity> m_TestEntity{ nullptr };
	Ref<Nut::Entity> m_Entity2{ nullptr };
	Ref<Nut::Entity> m_Entity3{ nullptr };

	Ref<Nut::Entity> m_Terrain{ nullptr };

	Nut::Timer m_UpdateTimer{};

	Nut::Scene m_Scene;
};



class SandboxApp : public Nut::Application
{
public:
	SandboxApp(const Nut::ApplicationSettings& settings)
		: Nut::Application(settings)
	{
		try
		{
			AttachLayer(CreateRef<SandboxLayer>("Sandbox"));
		}
		catch (Nut::Exception& ex)
		{
			LOG_CORE_ERROR("Exception: {}", ex.what());
		}
	}

};


Ref<Nut::Application> CreateApplication()
{
	Nut::ApplicationSettings settings{ .Width = 1280, .Height = 720, .VSync{true}, .Fullscreen{true} };

	Ref<SandboxApp> application{ nullptr };
	try
	{
		application = CreateRef<SandboxApp>(settings);
	}
	catch (Nut::Exception& ex)
	{
		LOG_CORE_ERROR("Failed to create application: {}", ex.what());
	}

	return application;
}
