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

		// FlatShader
		{
			ShaderSpecification shaderSpec{};
			shaderSpec.ShaderName = "FlatShader";
			shaderSpec.AddSourceFilePath(ShaderDomain::Vertex, "Assets/Shaders/FlatShader.vs");
			shaderSpec.AddSourceFilePath(ShaderDomain::Fragment, "Assets/Shaders/FlatShader.fs");

			Nut::ShaderLibrary::Add(Nut::OpenGLShader::Load(shaderSpec));
		}

		// TerrainShader
		{
			ShaderSpecification shaderSpec{};
			shaderSpec.ShaderName = "TerrainShader";
			shaderSpec.AddSourceFilePath(ShaderDomain::Vertex, "Assets/Shaders/TerrainShader.vs");
			shaderSpec.AddSourceFilePath(ShaderDomain::Fragment, "Assets/Shaders/TerrainShader.fs");

			Nut::ShaderLibrary::Add(Nut::OpenGLShader::Load(shaderSpec));
		}

		// Composition
		{
			ShaderSpecification shaderSpec{};
			shaderSpec.ShaderName = "CompositionShader";
			shaderSpec.AddSourceFilePath(ShaderDomain::Vertex, "Assets/Shaders/CompositionShader.vs");
			shaderSpec.AddSourceFilePath(ShaderDomain::Fragment, "Assets/Shaders/CompositionShader.fs");

			Nut::ShaderLibrary::Add(Nut::OpenGLShader::Load(shaderSpec));
		}

		return CreateRef<RendererContext>(windowWidth, windowHeight);
	}

	RendererContext::RendererContext(int32_t windowWidth, int32_t windowHeight)
	{
		s_ContextData.WindowWidth = windowWidth;
		s_ContextData.WindowHeight = windowHeight;

		glEnable(GL_DEPTH_TEST);
//		glDepthFunc(GL_ALWAYS);
		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);

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
