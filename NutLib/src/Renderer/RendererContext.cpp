#include "Renderer/RendererContext.h"

#include "Core/Log.h"
#include "Events/EventHandler.h"
#include "Renderer/Shader.h"

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


	Ref<RendererContext> RendererContext::Create(RendererAPI api, int32_t windowWidth, int32_t windowHeight)
	{
		s_RendererAPI = api;

		LOG_CORE_INFO("RenderContext created, size {},{}", windowWidth, windowHeight);

		// FlatShader - instanced
		{
			Nut::ShaderLibrary::Add(Nut::Shader::Load(ShaderDomain::Vertex, "FlatShader.Vertex", "Assets/Shaders/FlatShader.vs"));
			Nut::ShaderLibrary::Add(Nut::Shader::Load(ShaderDomain::Fragment, "FlatShader.Fragment", "Assets/Shaders/FlatShader.fs"));
		}
		// TerrainShader
		{

			Nut::ShaderLibrary::Add(Nut::Shader::Load(ShaderDomain::Vertex, "TerrainShader.Vertex", "Assets/Shaders/TerrainShader.vs"));
			Nut::ShaderLibrary::Add(Nut::Shader::Load(ShaderDomain::Fragment, "TerrainShader.Fragment", "Assets/Shaders/TerrainShader.fs"));
		}
		// CompositionShader
		{
			Nut::ShaderLibrary::Add(Nut::Shader::Load(ShaderDomain::Vertex, "CompositionShader.Vertex", "Assets/Shaders/CompositionShader.vs"));
			Nut::ShaderLibrary::Add(Nut::Shader::Load(ShaderDomain::Fragment, "CompositionShader.Fragment", "Assets/Shaders/CompositionShader.fs"));
		}
		// LineShader
		{
			Nut::ShaderLibrary::Add(Nut::Shader::Load(ShaderDomain::Vertex, "LineShader.Vertex", "Assets/Shaders/LineShader.vs"));
			Nut::ShaderLibrary::Add(Nut::Shader::Load(ShaderDomain::Fragment, "LineShader.Fragment", "Assets/Shaders/LineShader.fs"));
		}

		// Shader programs
		{
			Nut::ShaderLibrary::Add(Nut::Program::Link("FlatShader", { "FlatShader.Vertex", "FlatShader.Fragment" }));
			Nut::ShaderLibrary::Add(Nut::Program::Link("TerrainShader", { "TerrainShader.Vertex", "TerrainShader.Fragment" }));
			Nut::ShaderLibrary::Add(Nut::Program::Link("CompositionShader", { "CompositionShader.Vertex", "CompositionShader.Fragment" }));
			Nut::ShaderLibrary::Add(Nut::Program::Link("LineShader", { "LineShader.Vertex", "LineShader.Fragment" }));
		}

//			ShaderSpecification shaderSpec{};
//			shaderSpec.ShaderName = "FlatShader";
//			shaderSpec.AddSourceFilePath(ShaderDomain::Vertex, "Assets/Shaders/FlatShader.vs");
//			shaderSpec.AddSourceFilePath(ShaderDomain::Fragment, "Assets/Shaders/FlatShader.fs");
//
//			Nut::ShaderLibrary::Add(Nut::Shader::Load(shaderSpec));

		// TerrainShader
		{
//			ShaderSpecification shaderSpec{};
//			shaderSpec.ShaderName = "TerrainShader";
//			shaderSpec.AddSourceFilePath(ShaderDomain::Vertex, "Assets/Shaders/TerrainShader.vs");
//			shaderSpec.AddSourceFilePath(ShaderDomain::Fragment, "Assets/Shaders/TerrainShader.fs");
//
//			Nut::ShaderLibrary::Add(Nut::Shader::Load(shaderSpec));
		}

		// Composition
		{
//			ShaderSpecification shaderSpec{};
//			shaderSpec.ShaderName = "CompositionShader";
//			shaderSpec.AddSourceFilePath(ShaderDomain::Vertex, "Assets/Shaders/CompositionShader.vs");
//			shaderSpec.AddSourceFilePath(ShaderDomain::Fragment, "Assets/Shaders/CompositionShader.fs");
//
//			Nut::ShaderLibrary::Add(Nut::Shader::Load(shaderSpec));
		}

		// LineShader
		{
//			ShaderSpecification shaderSpec{};
//			shaderSpec.ShaderName = "LineShader";
//			shaderSpec.AddSourceFilePath(ShaderDomain::Vertex, "Assets/Shaders/LineShader.vs");
//			shaderSpec.AddSourceFilePath(ShaderDomain::Fragment, "Assets/Shaders/LineShader.fs");
//
//			Nut::ShaderLibrary::Add(Nut::Shader::Load(shaderSpec));
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
