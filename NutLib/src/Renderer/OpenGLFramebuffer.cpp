#include "Renderer/OpenGLFramebuffer.h"

#include "Core/Log.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Nut
{

	auto FramebufferAttachmentTypeToEnum(FramebufferAttachmentType type) -> GLenum
	{
		switch (type)
		{
			case FramebufferAttachmentType::Color: return GL_COLOR_ATTACHMENT0;
			case FramebufferAttachmentType::Depth: return GL_DEPTH_ATTACHMENT;
		}

		return GL_NONE;
	}


	auto OpenGLFramebuffer::Create(const FramebufferSpecification& specification) -> Ref<OpenGLFramebuffer>
	{
		return CreateRef<OpenGLFramebuffer>(specification);
	}


	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& specification)
		: m_Specification(specification)
	{
		glCreateFramebuffers(1, &m_ID);

		for (auto& attachmentSpec : specification.Attachments)
		{
			TextureSpecification textureSpec{};
			textureSpec.FramebufferAttachment = true;

			textureSpec.Width = specification.Width;
			textureSpec.Height = specification.Height;
			textureSpec.Format = attachmentSpec.Format;

			m_Attachments[attachmentSpec.Type] = Texture2D::Create(textureSpec);

			glNamedFramebufferTexture(m_ID, FramebufferAttachmentTypeToEnum(attachmentSpec.Type), m_Attachments[attachmentSpec.Type]->ID(), 0);

			if (glCheckNamedFramebufferStatus(m_ID, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				LOG_CORE_ERROR("Framebuffer is not complete!");
			}
		}


	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		if (m_ID != 0)
			glDeleteFramebuffers(1, &m_ID);
	}

	auto OpenGLFramebuffer::Clear() -> void
	{
		glm::vec4 clearColor{ 1.0f, 0.0f, 1.0f, 1.0f };
		float clearDepth = 0.0f;

		for (auto& [type, attachment] : m_Attachments)
		{
			switch (type)
			{
			case FramebufferAttachmentType::Color: glClearNamedFramebufferfv(m_ID, GL_COLOR, 0, glm::value_ptr(clearColor)); break;
			case FramebufferAttachmentType::Depth: glClearNamedFramebufferfv(m_ID, GL_DEPTH, 0, &clearDepth);  break;
			}
		}
	}

}
