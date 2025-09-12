#include "Renderer/OpenGLFramebuffer.h"



namespace Nut
{


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
		}

//		glNamedFramebufferTexture()

	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		if (m_ID != 0)
			glDeleteFramebuffers(1, &m_ID);
	}


}
