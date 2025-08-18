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

};



class SandboxApp : public Nut::Application
{
public:
	SandboxApp()
	{
		AttachLayer(CreateRef<SandboxLayer>("Sandbox"));
	}

};


Ref<Nut::Application> CreateApplication()
{
	return CreateRef<SandboxApp>();
}
