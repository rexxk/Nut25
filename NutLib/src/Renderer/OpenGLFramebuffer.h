#pragma once

#include "Core/Base.h"
#include "Renderer/Texture.h"

#include <glad/glad.h>

#include <cstdint>
#include <unordered_map>
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
		GLenum Format{ GL_RGBA };
	};

	struct FramebufferSpecification
	{
		uint32_t Width{ 1u };
		uint32_t Height{ 1u };

		std::vector<FramebufferAttachment> Attachments{};
	};


	class OpenGLFramebuffer
	{
	public:
		static auto Create(const FramebufferSpecification& specification) -> Ref<OpenGLFramebuffer>;

		OpenGLFramebuffer(const FramebufferSpecification& specification);
		~OpenGLFramebuffer();

		auto GetColorAttachment() -> Ref<Texture2D> { return m_Attachments[FramebufferAttachmentType::Color]; }
		auto GetDepthAttachment() -> Ref<Texture2D> { return m_Attachments[FramebufferAttachmentType::Depth]; }

		auto Clear() -> void;

		auto ID() const -> const GLuint { return m_ID; }

	private:
		GLuint m_ID{ 0 };

		FramebufferSpecification m_Specification{};

		std::unordered_map<FramebufferAttachmentType, Ref<Texture2D>> m_Attachments{};
	};


}
