#include <print>

#include "EntryPoint.h"
#include "NutLib.h"




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
	}

	virtual auto OnDetach() -> void override
	{
		std::println("Detaching {} layer", m_DebugName);
	}

	virtual auto OnUpdate() -> void override
	{
		m_RendererContext->BeginScene();
	}


private:
	Ref<Nut::RendererContext> m_RendererContext;
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
	Nut::ApplicationSettings settings{ .Width = 1280, .Height = 720, .Fullscreen = false };

	return CreateRef<SandboxApp>(settings);
}
