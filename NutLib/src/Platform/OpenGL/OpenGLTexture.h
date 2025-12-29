#pragma once

#include "Core/Base.h"
#include "Core/UUID.h"

#include "Renderer/Texture.h"


namespace Nut
{


	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const TextureSpecification& specification);
		virtual ~OpenGLTexture2D();

		virtual auto BindToSlot(uint32_t slot) -> void override;

		virtual auto TextureID() const -> const uint32_t override { return m_TextureID; }
		virtual auto ID() const -> const UUID override { return m_EntityID; }

	private:
		GLuint m_TextureID{ 0u };
		UUID m_EntityID{};
	};

	class OpenGLSampler : public Sampler
	{
	public:
		OpenGLSampler(SamplerFilterType filter);
		virtual ~OpenGLSampler();

		virtual auto ID() const -> const uint32_t override { return m_SamplerID; };

	private:
		uint32_t m_SamplerID{ 0u };
	};

}
