#pragma once

#include "Core/Base.h"
#include "Renderer/Framebuffer.h"
#include "Renderer/Texture.h"

#include <glad/glad.h>

#include <cstdint>
#include <unordered_map>
#include <vector>


namespace Nut
{


	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& specification);
		virtual ~OpenGLFramebuffer();

		virtual auto GetColorAttachment() -> Ref<Texture2D> override { return m_Attachments[FramebufferAttachmentType::Color]; }
		virtual auto GetDepthAttachment() -> Ref<Texture2D> override { return m_Attachments[FramebufferAttachmentType::Depth]; }

		virtual auto Clear() -> void override;

		virtual auto ID() const -> const uint32_t override { return m_ID; }

	private:
		auto Resize() -> void;

	private:
		GLuint m_ID{ 0 };

		FramebufferSpecification m_Specification{};

		std::unordered_map<FramebufferAttachmentType, Ref<Texture2D>> m_Attachments{};
	};


}
