#include "Renderer/Texture.h"
#include "Renderer/RendererContext.h"

#include "Platform/OpenGL/OpenGLTexture.h"


#include "Core/Log.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>



namespace Nut
{


	auto Texture2D::Create(const TextureSpecification& specification) -> Ref<Texture2D>
	{
		switch (RendererContext::API())
		{
			case RendererAPI::OpenGL: return CreateRef<OpenGLTexture2D>(specification);
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



	auto TextureLibrary::Add(const std::string& textureName, Ref<Texture2D> texture) -> void
	{
		if (s_Textures.contains(textureName))
		{
			LOG_CORE_WARN("Texture {} already exists in TextureLibrary", textureName);
			return;
		}

		s_Textures[textureName] = texture;
	}

	auto TextureLibrary::Get(const std::string& textureName) -> Ref<Texture2D>
	{
		if (s_Textures.contains(textureName))
			return s_Textures[textureName];

		return nullptr;
	}

}
