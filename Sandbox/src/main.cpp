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
	}

	virtual auto OnDetach() -> void override
	{
		std::println("Detaching {} layer", m_DebugName);
	}

	virtual auto OnUpdate() -> void override
	{
		Nut::Renderer::Clear();
	}

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
	Nut::ApplicationSettings settings{ .Fullscreen = true };

	return CreateRef<SandboxApp>(settings);
}
