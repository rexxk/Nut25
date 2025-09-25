#include <print>

#include "EntryPoint.h"
#include "NutLib.h"

#include <print>
#include <vector>



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
		auto meshID = Nut::AssetManager::AddMesh(Nut::Mesh::CreateTriangle());


		Nut::TextureSpecification texSpec{};
		texSpec.Filepath = "Assets/Textures/texture.png";
//		texSpec.Filepath = "C:/Programming/Private/Nut25/Sandbox/Assets/Textures/texture.png";
//		texSpec.Format = GL_RGBA;
//		texSpec.UnitTexture = true;
//		texSpec.Color = glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f };
		

		Ref<Nut::Texture2D> texture = Nut::Texture2D::Create(texSpec);

		m_TestEntity = Nut::Entity::Create(meshID, texture);

		m_Scene.AddEntity(m_TestEntity);
	}

	virtual auto OnDetach() -> void override
	{
		std::println("Detaching {} layer", m_DebugName);
	}

	virtual auto OnUpdate(double timestep) -> void override
	{
		m_RendererContext->BeginScene();

		m_Scene.Update(timestep);
		m_Scene.Draw();
	}


private:
	Ref<Nut::RendererContext> m_RendererContext;

	Ref<Nut::Buffer> m_VertexData{ nullptr };
	Ref<Nut::Buffer> m_IndexData{ nullptr };

	Ref<Nut::Entity> m_TestEntity{ nullptr };

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
