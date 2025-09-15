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
		glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);

		if (specification.UnitTexture)
		{

			glTextureStorage2D(m_ID, 1, specification.Format == GL_RGBA ? GL_RGBA8 : GL_RGB8, 1, 1);
			glTextureSubImage2D(m_ID, 0, 0, 0, 1, 1, specification.Format, GL_FLOAT, glm::value_ptr(specification.Color));

			LOG_CORE_INFO("Unit texture created");
		}
		else if (specification.FramebufferAttachment)
		{
			glTextureStorage2D(m_ID, 1, specification.Format, specification.Width, specification.Height);
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

			glTextureStorage2D(m_ID, 1, specification.Format == GL_RGBA ? GL_RGBA8 : GL_RGB8, imageWidth, imageHeight);
			glTextureSubImage2D(m_ID, 0, 0, 0, imageWidth, imageHeight, specification.Format, GL_UNSIGNED_BYTE, imagePixels);

			stbi_image_free(imagePixels);
		}


		glGenerateTextureMipmap(m_ID);
	}

	Texture2D::~Texture2D()
	{
		if (m_ID != 0)
			glDeleteTextures(1, &m_ID);
	}


	auto Texture2D::BindToSlot(uint32_t slot) -> void
	{
		glBindTextureUnit(slot, m_ID);
	}



	auto Sampler::Create(GLenum filter) -> Ref<Sampler>
	{
		return CreateRef<Sampler>(filter);
	}

	Sampler::Sampler(GLenum filter)
	{
		glCreateSamplers(1, &m_ID);

		glSamplerParameteri(m_ID, GL_TEXTURE_MIN_FILTER, filter);
		glSamplerParameteri(m_ID, GL_TEXTURE_MAG_FILTER, filter);
		glSamplerParameteri(m_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glSamplerParameteri(m_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	Sampler::~Sampler()
	{
		if (m_ID != 0)
			glDeleteSamplers(1, &m_ID);
	}


}
