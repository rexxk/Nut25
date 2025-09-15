#include "Renderer/OpenGLFramebuffer.h"



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
		}


	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		if (m_ID != 0)
			glDeleteFramebuffers(1, &m_ID);
	}


}
