#include "Renderer/RendererContext.h"

#include "Core/Log.h"
#include "Events/EventHandler.h"
#include "Renderer/OpenGLShader.h"

#include <cstdint>
#include <format>
#include <print>

#include <glad/glad.h>



namespace Nut
{


	struct ContextData
	{
		int32_t WindowWidth{ 0 };
		int32_t WindowHeight{ 0 };

	};

	static ContextData s_ContextData{ 0 };


	Ref<RendererContext> RendererContext::Create(int32_t windowWidth, int32_t windowHeight)
	{
		LOG_CORE_INFO("RenderContext created, size {},{}", windowWidth, windowHeight);

		Nut::ShaderLibrary::Add(Nut::OpenGLShader::LoadFlatShader());
		Nut::ShaderLibrary::Add(Nut::OpenGLShader::LoadCompositionShader());

		return CreateRef<RendererContext>(windowWidth, windowHeight);
	}

	RendererContext::RendererContext(int32_t windowWidth, int32_t windowHeight)
	{
		s_ContextData.WindowWidth = windowWidth;
		s_ContextData.WindowHeight = windowHeight;

		EventHandler::Subscribe(EventType::WindowSize, [&](Ref<Event> event)
			{
				Ref<WindowResizedEvent> e = std::dynamic_pointer_cast<WindowResizedEvent>(event);
				s_ContextData.WindowWidth = e->Width();
				s_ContextData.WindowHeight = e->Height();

			});
	}

	auto RendererContext::BeginScene() -> void
	{
//		glViewport(0, 0, s_ContextData.WindowWidth, s_ContextData.WindowHeight);

		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

}
