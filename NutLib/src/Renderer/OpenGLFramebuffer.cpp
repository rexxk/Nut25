#include "Renderer/OpenGLFramebuffer.h"

#include "Core/Log.h"
#include "Events/EventHandler.h"

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
		Resize();

		if (m_Specification.Resizeable)
		{
			EventHandler::Subscribe(EventType::WindowSize, [&](Ref<Event> event)
				{
					Ref<WindowResizedEvent> e = std::dynamic_pointer_cast<WindowResizedEvent>(event);

					m_Specification.Width = static_cast<uint32_t>(e->Width());
					m_Specification.Height = static_cast<uint32_t>(e->Height());

					Resize();
				});
		}
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		if (m_ID != 0)
			glDeleteFramebuffers(1, &m_ID);
	}

	auto OpenGLFramebuffer::Resize() -> void
	{
		if (m_ID != 0)
			glDeleteFramebuffers(1, &m_ID);

		if (!m_Attachments.empty())
			m_Attachments.clear();

		glCreateFramebuffers(1, &m_ID);

		for (auto& attachmentSpec : m_Specification.Attachments)
		{
			TextureSpecification textureSpec{};
			textureSpec.FramebufferAttachment = true;

			textureSpec.Width = m_Specification.Width;
			textureSpec.Height = m_Specification.Height;
			textureSpec.Format = attachmentSpec.Format;

			m_Attachments[attachmentSpec.Type].reset(new Texture2D(textureSpec));

			glNamedFramebufferTexture(m_ID, FramebufferAttachmentTypeToEnum(attachmentSpec.Type), m_Attachments[attachmentSpec.Type]->TextureID(), 0);
		}

		if (glCheckNamedFramebufferStatus(m_ID, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			LOG_CORE_ERROR("Framebuffer is not complete!");
		}

	}

	auto OpenGLFramebuffer::Clear() -> void
	{
		glm::vec4 clearColor{ 1.0f, 0.0f, 1.0f, 1.0f };
		float clearDepth = 1.0f;

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
