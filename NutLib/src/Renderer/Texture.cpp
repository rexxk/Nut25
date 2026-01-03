#include "Renderer/Texture.h"
#include "Renderer/RendererContext.h"

#include "Platform/OpenGL/OpenGLTexture.h"


#include "Core/Log.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>



namespace Nut
{


	auto Texture2D::Create(const TextureSpecification& specification) -> Scope<Texture2D>
	{
		switch (RendererContext::API())
		{
			case RendererAPI::OpenGL: return CreateScope<OpenGLTexture2D>(specification);
		}

		return nullptr;
	}

//	auto Texture2D::CreatePointer(const TextureSpecification& specification) -> Ref<Texture2D>
//	{
//		switch (RendererContext::API())
//		{
//		case RendererAPI::OpenGL: return CreateRef<OpenGLTexture2D>(specification);
//		}
//
//		return nullptr;
//	}


	auto Sampler::Create(SamplerFilterType filter) -> Ref<Sampler>
	{
		switch (RendererContext::API())
		{
			case RendererAPI::OpenGL: return CreateRef<OpenGLSampler>(filter);
		}

		return nullptr;
	}


}
