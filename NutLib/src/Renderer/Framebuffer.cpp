#include "Renderer/Framebuffer.h"
#include "Renderer/RendererContext.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"


namespace Nut
{

	auto Framebuffer::Create(const FramebufferSpecification& specification) -> Ref<Framebuffer>
	{
		switch (RendererContext::API())
		{
			case RendererAPI::OpenGL: return CreateRef<OpenGLFramebuffer>(specification);
		}

		return nullptr;
	}



}
