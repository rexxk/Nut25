#pragma once

#include "Core/Base.h"
#include "Renderer/Texture.h"

#include <cstdint>
#include <vector>


namespace Nut
{


	enum class FramebufferAttachmentType
	{
		Color,
		Depth,
	};

	struct FramebufferAttachment
	{
		FramebufferAttachmentType Type;
		uint32_t Format{};
	};

	struct FramebufferSpecification
	{
		uint32_t Width{ 1u };
		uint32_t Height{ 1u };

		bool Resizeable{ true };

		std::vector<FramebufferAttachment> Attachments{};
	};


	class Framebuffer
	{
	public:
		static auto Create(const FramebufferSpecification& specification) -> Ref<Framebuffer>;

		Framebuffer() = default;
		virtual ~Framebuffer() = default;
	
		virtual auto GetColorAttachment() -> Ref<Texture2D> { return nullptr; }
		virtual auto GetDepthAttachment() -> Ref<Texture2D> { return nullptr; }

		virtual auto Clear() -> void {};

		virtual auto ID() const -> const uint32_t = 0;
	};


}
