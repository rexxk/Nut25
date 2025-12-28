#include "Platform/OpenGL/OpenGLShader.h"

#include "Core/Log.h"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <string>

namespace Nut
{

	auto DomainToString(ShaderDomain domain) -> std::string
	{
		switch (domain)
		{
		case ShaderDomain::Vertex: return "Vertex";
		case ShaderDomain::Fragment: return "Fragment";
		case ShaderDomain::Geometry: return "Geometry";
		case ShaderDomain::Compute: return "Compute";
		}

		return "unknown";
	}

	auto ToNative(ShaderDomain domain) -> GLuint
	{
		switch (domain)
		{
		case ShaderDomain::Vertex: return GL_VERTEX_SHADER;
		case ShaderDomain::Fragment: return GL_FRAGMENT_SHADER;
		case ShaderDomain::Geometry: return GL_GEOMETRY_SHADER;
		case ShaderDomain::Compute: return GL_COMPUTE_SHADER;
		}

		return GL_NONE;
	}


	auto LoadSourceFileFromFile(const std::string& filepath) -> std::string
	{
		std::string source;

		auto fs = std::ifstream(filepath, std::ios::in | std::ios::binary);

		if (!fs.is_open())
		{
			LOG_CORE_ERROR("Unable to open shader file {}", filepath);
			return "";
		}

		fs.seekg(0, fs.end);
		auto length = fs.tellg();
		fs.seekg(0, fs.beg);

		source.resize(length);

		fs.read((char*)source.data(), length);

		fs.close();

		return source;
	}


	OpenGLShader::OpenGLShader(const ShaderSpecification& specification)
		: Shader(specification.ShaderName)
	{

//		for (auto [domain, source] : specification.SourceFiles)
//		{
//			m_ShaderSources[domain] = LoadSourceFileFromFile(source);
//		}
//
//		Reload();
	}

	OpenGLShader::OpenGLShader(ShaderDomain domain, const std::string& shaderName, const std::filesystem::path& filepath)
		: Shader(shaderName), m_Domain(domain)
	{
		m_ShaderSource = LoadSourceFileFromFile(filepath.string());

		Reload();
	}

	OpenGLShader::OpenGLShader(const std::string& shaderName, const std::unordered_map<ShaderDomain, std::string>& shaderSources)
		: Shader(shaderName)
	{
//		m_ShaderSources = shaderSources;
//		Reload();
	}

	OpenGLShader::~OpenGLShader()
	{
		if (m_ShaderID != 0)
			glDeleteShader(m_ShaderID);

	}

	auto OpenGLShader::Reload() -> void
	{
		Compile();
//		CompileAndLink();
	}

	auto OpenGLShader::Compile() -> void
	{
		LOG_CORE_INFO(" Shader: {}", DomainToString(m_Domain));

		m_ShaderID = glCreateShader(ToNative(m_Domain));

		const GLchar* glSource = m_ShaderSource.data();
		GLint sourceLength = static_cast<GLint>(m_ShaderSource.size());

		glShaderSource(m_ShaderID, 1u, &glSource, &sourceLength);
		glCompileShader(m_ShaderID);

		GLint status{};
		glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &status);

		if (status == GL_FALSE)
		{
			GLint infoLogLength{};
			glGetShaderiv(m_ShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

			std::string infoLog;
			infoLog.resize(static_cast<size_t>(infoLogLength));
			glGetShaderInfoLog(m_ShaderID, infoLogLength, &infoLogLength, infoLog.data());

			LOG_CORE_ERROR("Shader error:\n{}", infoLog);

			return;
		}

	}






}
