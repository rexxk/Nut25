#include "Renderer/OpenGLShader.h"


#include "Core/Log.h"

#include <string>
#include <unordered_map>


namespace Nut
{


	auto DomainToString(OpenGLShader::Domain domain) -> std::string
	{
		switch (domain)
		{
			case OpenGLShader::Domain::Vertex: return "Vertex";
			case OpenGLShader::Domain::Fragment: return "Fragment";
			case OpenGLShader::Domain::Geometry: return "Geometry";
			case OpenGLShader::Domain::Compute: return "Compute";
		}

		return "unknown";
	}

	auto DomainToGLShader(OpenGLShader::Domain domain) -> GLuint
	{
		switch (domain)
		{
			case OpenGLShader::Domain::Vertex: return GL_VERTEX_SHADER;
			case OpenGLShader::Domain::Fragment: return GL_FRAGMENT_SHADER;
			case OpenGLShader::Domain::Geometry: return GL_GEOMETRY_SHADER;
			case OpenGLShader::Domain::Compute: return GL_COMPUTE_SHADER;
		}

		return GL_NONE;
	}

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
		return CreateRef<OpenGLShader>("FlatShader", s_FlatShaderSources);
	}


	OpenGLShader::OpenGLShader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentShaderPath)
	{

	}

	OpenGLShader::OpenGLShader(const std::string& shaderName, const std::unordered_map<Domain, std::string>& shaderSources)
		: m_ShaderSources(shaderSources)
	{
		LOG_CORE_INFO("Compiling shader: {}", shaderName);

		Reload();
	}

	OpenGLShader::~OpenGLShader()
	{
		if (m_ProgramID != -1)
			glDeleteProgram(m_ProgramID);
	}

	auto OpenGLShader::Reload() -> void
	{
		CompileAndLink();
	}

	auto OpenGLShader::CompileAndLink() -> void
	{
		std::vector<GLuint> shaders{};

		for (auto &[domain, source] : m_ShaderSources)
		{
			std::string domainString = DomainToString(domain);
			LOG_CORE_INFO(" Shader: {}", domainString);
	
			GLuint shader = glCreateShader(DomainToGLShader(domain));

			const GLchar* glSource = source.data();
			GLint sourceLength = static_cast<GLint>(source.size());

			glShaderSource(shader, 1u, &glSource, &sourceLength);
			glCompileShader(shader);

			GLint status{};
			glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

			if (status == GL_FALSE)
			{
				GLint infoLogLength{};
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

				std::string infoLog;
				infoLog.resize(static_cast<size_t>(infoLogLength));
				glGetShaderInfoLog(shader, infoLogLength, &infoLogLength, infoLog.data());

				LOG_CORE_ERROR("Shader error:\n{}", infoLog);

				return;
			}

			shaders.push_back(shader);
		}

		if (m_ProgramID != -1)
			glDeleteProgram(m_ProgramID);

		m_ProgramID = glCreateProgram();

		for (auto& shader : shaders)
		{
			glAttachShader(m_ProgramID, shader);
		}

		glLinkProgram(m_ProgramID);

		GLint linkStatus{};
		glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &linkStatus);

		if (linkStatus == GL_FALSE)
		{
			GLint infoLogLength{};
			glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);

			std::string infoLog;
			infoLog.resize(static_cast<size_t>(infoLogLength));
			glGetProgramInfoLog(m_ProgramID, infoLogLength, &infoLogLength, infoLog.data());

			LOG_CORE_ERROR("Link error:\n{}", infoLog);
		}


		for (auto& shader : shaders)
		{
			glDeleteShader(shader);
		}

	}

	auto OpenGLShader::Bind() const -> void
	{
		glUseProgram(m_ProgramID);
	}

}
