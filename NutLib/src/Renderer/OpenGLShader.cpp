#include "Renderer/OpenGLShader.h"


#include <string>
#include <unordered_map>


namespace Nut
{



	std::unordered_map<OpenGLShader::Domain, std::string> s_FlatShaderSources{
		{
			OpenGLShader::Domain::Vertex,
			R"(
				#version 450 core

				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;

				out vec4 v_Color;

				void main()
				{
					gl_Position = vec4(a_Position, 1.0);
					v_Color = a_Color;
				}
			)"
		},
		{
			OpenGLShader::Domain::Fragment,
			R"(
				#version 450 core

				out vec4 o_Color;
				in vec4 v_Color;

				void main()
				{
					o_Color = v_Color;
				}

			)"
		}
	};


	auto OpenGLShader::LoadFromFile(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentShaderPath) -> Ref<OpenGLShader>
	{
		return CreateRef<OpenGLShader>(vertexShaderPath, fragmentShaderPath);
	}

	auto OpenGLShader::LoadFlatShader() -> Ref<OpenGLShader>
	{
		return CreateRef<OpenGLShader>(s_FlatShaderSources);
	}


	OpenGLShader::OpenGLShader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentShaderPath)
	{

	}

	OpenGLShader::OpenGLShader(const std::unordered_map<Domain, std::string>& shaderSources)
	{

	}

}
