#include "Renderer/OpenGLFramebuffer.h"



namespace Nut
{


	OpenGLFramebuffer::OpenGLFramebuffer()
	{
		glCreateFramebuffers(1, &m_ID);

//		glNamedFramebufferTexture()

	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		if (m_ID != 0)
			glDeleteFramebuffers(1, &m_ID);
	}


}
