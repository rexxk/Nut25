#pragma once

#include "Core/Base.h"
#include "Core/UUID.h"

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

		uint32_t Format{ 0u };

		bool UnitTexture{ false };
		glm::vec4 Color{ 1.0f, 0.0f, 1.0f, 1.0f };

		bool FramebufferAttachment{ false };
	};


	class Texture2D
	{
	public:
		static auto Create(const TextureSpecification& specification) -> Ref<Texture2D>;

		Texture2D() = default;
		virtual ~Texture2D() = default;

		virtual auto BindToSlot(uint32_t slot) -> void {}

		virtual auto TextureID() const -> const uint32_t = 0;
		virtual auto ID() const -> const UUID { return UUID(); }
	};


	class Sampler
	{
	public:
		static auto Create(SamplerFilterType filter) -> Ref<Sampler>;

		Sampler() = default;
		virtual ~Sampler() = default;

		virtual auto ID() const -> const uint32_t = 0;
	};

}
