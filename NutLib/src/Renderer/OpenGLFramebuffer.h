#pragma once

#include <glad/glad.h>


namespace Nut
{


	class OpenGLFramebuffer
	{
	public:
		OpenGLFramebuffer();
		~OpenGLFramebuffer();

		auto ID() const -> const GLuint { return m_ID; }

	private:
		GLuint m_ID{ 0 };
	};


}
