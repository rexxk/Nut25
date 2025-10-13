#pragma once

#include "Core/Base.h"

#include <cstdint>
#include <filesystem>

#include <glad/glad.h>
#include <glm/glm.hpp>


namespace Nut
{


	enum SamplerFilterType
	{
		Nearest,
		Linear,
	};


	struct TextureSpecification
	{
		uint32_t Width{ 1u };
		uint32_t Height{ 1u };

		std::filesystem::path Filepath{};

		GLenum Format{ GL_RGBA };

		bool UnitTexture{ false };
		glm::vec4 Color{ 1.0f, 0.0f, 1.0f, 1.0f };

		bool FramebufferAttachment{ false };
	};


	class Texture2D
	{
	public:
		static auto Create(const TextureSpecification& specification) -> Ref<Texture2D>;

		Texture2D(const TextureSpecification& specification);
		~Texture2D();

		auto BindToSlot(uint32_t slot) -> void;

		auto ID() const -> const GLuint { return m_ID; }


	private:
		GLuint m_ID{ 0 };
	};


	class Sampler
	{
	public:
		static auto Create(SamplerFilterType filter) -> Ref<Sampler>;

		Sampler(SamplerFilterType filter);
		~Sampler();

		auto ID() const -> const GLuint { return m_ID; }

	private:
		GLuint m_ID{ 0 };
	};

}
