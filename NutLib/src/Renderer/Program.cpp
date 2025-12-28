#include "Renderer/Program.h"
#include "Platform/OpenGL/OpenGLProgram.h"

#include "Renderer/RendererContext.h"



namespace Nut
{


	auto Program::Link(const std::string& programName, const std::vector<std::string>& shaderList) -> Ref<Program>
	{
		switch (RendererContext::API())
		{
			case RendererAPI::OpenGL: return CreateRef<OpenGLProgram>(programName, shaderList);
			case RendererAPI::Vulkan: return nullptr;
		}
	
		return nullptr;
	}

}
