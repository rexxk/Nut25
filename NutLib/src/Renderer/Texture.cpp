#include "Renderer/Texture.h"


#include "Core/Log.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


namespace Nut
{


	auto Texture2D::Create(const TextureSpecification& specification) -> Ref<Texture2D>
	{
		return CreateRef<Texture2D>(specification);
	}

	 
	Texture2D::Texture2D(const TextureSpecification& specification)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_Handle);

		if (specification.UnitTexture)
		{

			glTextureStorage2D(m_Handle, 1, specification.Format == GL_RGBA ? GL_RGBA8 : GL_RGB8, 1, 1);
			glTextureSubImage2D(m_Handle, 0, 0, 0, 1, 1, specification.Format, GL_FLOAT, glm::value_ptr(specification.Color));

			LOG_CORE_INFO("Unit texture created");
		}
		else if (specification.FramebufferAttachment)
		{
			glTextureStorage2D(m_Handle, 1, specification.Format, specification.Width, specification.Height);
//			glTextureSubImage2D(m_ID, 0, 0, 0, specification.Width, specification.Height, specification.Format, GL_UNSIGNED_BYTE, nullptr);
		}
		else
		{
			int32_t imageWidth{ 0 };
			int32_t imageHeight{ 0 };
			int32_t imageBitsPerPixel{ 0 };

			stbi_set_flip_vertically_on_load(true);
			stbi_uc* imagePixels = stbi_load(specification.Filepath.string().c_str(), &imageWidth, &imageHeight, &imageBitsPerPixel, 4);

			if (imagePixels == nullptr)
			{
				std::string filename = specification.Filepath.string();
				LOG_CORE_ERROR("Failed to load texture: {}", filename);
				return;
			}

			GLsizei levels = 1 + static_cast<GLsizei>(std::floor(std::log2(std::max(imageWidth, imageHeight))));

			glTextureStorage2D(m_Handle, levels, specification.Format == GL_RGBA ? GL_RGBA8 : GL_RGB8, imageWidth, imageHeight);
			glTextureSubImage2D(m_Handle, 0, 0, 0, imageWidth, imageHeight, specification.Format, GL_UNSIGNED_BYTE, imagePixels);

			glGenerateTextureMipmap(m_Handle);

			stbi_image_free(imagePixels);
		}


	}

	Texture2D::~Texture2D()
	{
		if (m_ID != 0)
			glDeleteTextures(1, &m_Handle);
	}


	auto Texture2D::BindToSlot(uint32_t slot) -> void
	{
		glBindTextureUnit(slot, m_Handle);
	}



	auto FilterTypeToEnum(SamplerFilterType filterType) -> GLenum
	{
		switch (filterType)
		{
			case SamplerFilterType::Linear: return GL_LINEAR_MIPMAP_LINEAR;
			case SamplerFilterType::Nearest: return GL_NEAREST_MIPMAP_NEAREST;
		}
		
		return GL_NEAREST_MIPMAP_NEAREST;
	}


	auto Sampler::Create(SamplerFilterType filter) -> Ref<Sampler>
	{
		return CreateRef<Sampler>(filter);
	}

	Sampler::Sampler(SamplerFilterType filter)
	{
		glCreateSamplers(1, &m_ID);

		glSamplerParameteri(m_ID, GL_TEXTURE_MIN_FILTER, FilterTypeToEnum(filter));
		glSamplerParameteri(m_ID, GL_TEXTURE_MAG_FILTER, FilterTypeToEnum(filter));
		glSamplerParameteri(m_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glSamplerParameteri(m_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glSamplerParameterf(m_ID, GL_TEXTURE_MAX_ANISOTROPY, 16.0f);
	}

	Sampler::~Sampler()
	{
		if (m_ID != 0)
			glDeleteSamplers(1, &m_ID);
	}


}
