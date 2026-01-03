#include "Platform/OpenGL/OpenGLTexture.h"


#include "Core/Log.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


namespace Nut
{


	OpenGLTexture2D::OpenGLTexture2D(const TextureSpecification& specification)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);

		if (specification.UnitTexture)
		{

			glTextureStorage2D(m_TextureID, 1, specification.Format == GL_RGBA ? GL_RGBA8 : GL_RGB8, 1, 1);
			glTextureSubImage2D(m_TextureID, 0, 0, 0, 1, 1, specification.Format, GL_FLOAT, glm::value_ptr(specification.Color));

			LOG_CORE_INFO("Unit texture created");
		}
		else if (specification.FramebufferAttachment)
		{
			glTextureStorage2D(m_TextureID, 1, specification.Format, specification.Width, specification.Height);
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

			glTextureStorage2D(m_TextureID, levels, specification.Format == GL_RGBA ? GL_RGBA8 : GL_RGB8, imageWidth, imageHeight);
			glTextureSubImage2D(m_TextureID, 0, 0, 0, imageWidth, imageHeight, specification.Format, GL_UNSIGNED_BYTE, imagePixels);

			glGenerateTextureMipmap(m_TextureID);

			stbi_image_free(imagePixels);
		}


	}

	OpenGLTexture2D::OpenGLTexture2D(const OpenGLTexture2D& other)
	{
		m_TextureID = other.m_TextureID;
		m_EntityID = other.m_EntityID;
	}

	OpenGLTexture2D::OpenGLTexture2D(OpenGLTexture2D&& other)
	{
		m_TextureID = other.m_TextureID;
		m_EntityID = other.m_EntityID;
	}

	OpenGLTexture2D& OpenGLTexture2D::operator=(const OpenGLTexture2D& other)
	{
		m_TextureID = other.m_TextureID;
		m_EntityID = other.m_EntityID;

		return *this;
	}
	
	OpenGLTexture2D& OpenGLTexture2D::operator=(const OpenGLTexture2D && other)
	{
		m_TextureID = other.m_TextureID;
		m_EntityID = other.m_EntityID;

		return *this;
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		if (m_TextureID != 0)
			glDeleteTextures(1, &m_TextureID);
	}


	auto OpenGLTexture2D::BindToSlot(uint32_t slot) -> void
	{
		glBindTextureUnit(slot, m_TextureID);
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




	OpenGLSampler::OpenGLSampler(SamplerFilterType filter)
	{
		glCreateSamplers(1, &m_SamplerID);

		glSamplerParameteri(m_SamplerID, GL_TEXTURE_MIN_FILTER, FilterTypeToEnum(filter));
		glSamplerParameteri(m_SamplerID, GL_TEXTURE_MAG_FILTER, FilterTypeToEnum(filter));
		glSamplerParameteri(m_SamplerID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glSamplerParameteri(m_SamplerID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glSamplerParameterf(m_SamplerID, GL_TEXTURE_MAX_ANISOTROPY, 16.0f);
	}

	OpenGLSampler::~OpenGLSampler()
	{
		if (m_SamplerID != 0)
			glDeleteSamplers(1, &m_SamplerID);
	}




}
