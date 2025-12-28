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

	auto EnumLength(GLenum type) -> uint32_t
	{
		switch (type)
		{
		case GL_FLOAT: return sizeof(GLfloat);
		case GL_FLOAT_VEC2: return 2 * sizeof(GLfloat);
		case GL_FLOAT_VEC3: return 3 * sizeof(GLfloat);
		case GL_FLOAT_VEC4: return 4 * sizeof(GLfloat);
		case GL_FLOAT_MAT2: return 2 * 2 * sizeof(GLfloat);
		case GL_FLOAT_MAT3: return 3 * 3 * sizeof(GLfloat);
		case GL_FLOAT_MAT4: return 4 * 4 * sizeof(GLfloat);
		case GL_FLOAT_MAT2x3: return 2 * 3 * sizeof(GLfloat);
		case GL_FLOAT_MAT2x4: return 2 * 4 * sizeof(GLfloat);
		case GL_FLOAT_MAT3x2: return 3 * 2 * sizeof(GLfloat);
		case GL_FLOAT_MAT3x4: return 3 * 4 * sizeof(GLfloat);
		case GL_FLOAT_MAT4x2: return 4 * 2 * sizeof(GLfloat);
		case GL_FLOAT_MAT4x3: return 4 * 3 * sizeof(GLfloat);
		case GL_INT: return sizeof(GLint);
		case GL_INT_VEC2: return 2 * sizeof(GLint);
		case GL_INT_VEC3: return 3 * sizeof(GLint);
		case GL_INT_VEC4: return 4 * sizeof(GLint);
		case GL_UNSIGNED_INT: return sizeof(GLuint);
		case GL_UNSIGNED_INT_VEC2: return 2 * sizeof(GLuint);
		case GL_UNSIGNED_INT_VEC3: return 3 * sizeof(GLuint);
		case GL_UNSIGNED_INT_VEC4: return 4 * sizeof(GLuint);
		case GL_DOUBLE: return sizeof(GLdouble);
		case GL_DOUBLE_VEC2: return 2 * sizeof(GLdouble);
		case GL_DOUBLE_VEC3: return 3 * sizeof(GLdouble);
		case GL_DOUBLE_VEC4: return 4 * sizeof(GLdouble);
		case GL_DOUBLE_MAT2: return 2 * 2 * sizeof(GLdouble);
		case GL_DOUBLE_MAT3: return 3 * 3 * sizeof(GLdouble);
		case GL_DOUBLE_MAT4: return 4 * 4 * sizeof(GLdouble);
		case GL_DOUBLE_MAT2x3: return 2 * 3 * sizeof(GLdouble);
		case GL_DOUBLE_MAT2x4: return 2 * 4 * sizeof(GLdouble);
		case GL_DOUBLE_MAT3x2: return 3 * 2 * sizeof(GLdouble);
		case GL_DOUBLE_MAT3x4: return 3 * 4 * sizeof(GLdouble);
		case GL_DOUBLE_MAT4x2: return 4 * 2 * sizeof(GLdouble);
		case GL_DOUBLE_MAT4x3: return 4 * 3 * sizeof(GLdouble);
		}

		return 4;
	}

	auto ToNative(GLenum type) -> GLenum
	{
		switch (type)
		{
		case GL_FLOAT: return GL_FLOAT;
		case GL_FLOAT_VEC2: return GL_FLOAT;
		case GL_FLOAT_VEC3: return GL_FLOAT;
		case GL_FLOAT_VEC4: return GL_FLOAT;
		case GL_FLOAT_MAT2: return GL_FLOAT;
		case GL_FLOAT_MAT3: return GL_FLOAT;
		case GL_FLOAT_MAT4: return GL_FLOAT;
		case GL_FLOAT_MAT2x3: return GL_FLOAT;
		case GL_FLOAT_MAT2x4: return GL_FLOAT;
		case GL_FLOAT_MAT3x2: return GL_FLOAT;
		case GL_FLOAT_MAT3x4: return GL_FLOAT;
		case GL_FLOAT_MAT4x2: return GL_FLOAT;
		case GL_FLOAT_MAT4x3: return GL_FLOAT;
		case GL_INT: return GL_INT;
		case GL_INT_VEC2: return GL_INT;
		case GL_INT_VEC3: return GL_INT;
		case GL_INT_VEC4: return GL_INT;
		case GL_UNSIGNED_INT: return GL_UNSIGNED_INT;
		case GL_UNSIGNED_INT_VEC2: GL_UNSIGNED_INT;
		case GL_UNSIGNED_INT_VEC3: GL_UNSIGNED_INT;
		case GL_UNSIGNED_INT_VEC4: GL_UNSIGNED_INT;
		case GL_DOUBLE: return GL_DOUBLE;
		case GL_DOUBLE_VEC2: return GL_DOUBLE;
		case GL_DOUBLE_VEC3: return GL_DOUBLE;
		case GL_DOUBLE_VEC4: return GL_DOUBLE;
		case GL_DOUBLE_MAT2: return GL_DOUBLE;
		case GL_DOUBLE_MAT3: return GL_DOUBLE;
		case GL_DOUBLE_MAT4: return GL_DOUBLE;
		case GL_DOUBLE_MAT2x3: return GL_DOUBLE;
		case GL_DOUBLE_MAT2x4: return GL_DOUBLE;
		case GL_DOUBLE_MAT3x2: return GL_DOUBLE;
		case GL_DOUBLE_MAT3x4: return GL_DOUBLE;
		case GL_DOUBLE_MAT4x2: return GL_DOUBLE;
		case GL_DOUBLE_MAT4x3: return GL_DOUBLE;
		}

		return GL_FLOAT;
	}

	auto EnumCount(GLenum type) -> GLuint
	{
		switch (type)
		{
		case GL_FLOAT: return 1u;
		case GL_FLOAT_VEC2: return 2u;
		case GL_FLOAT_VEC3: return 3u;
		case GL_FLOAT_VEC4: return 4u;
		case GL_FLOAT_MAT2: return 2u * 2u;
		case GL_FLOAT_MAT3: return 3u * 3u;
		case GL_FLOAT_MAT4: return 4u * 4u;
		case GL_FLOAT_MAT2x3: return 2u * 3u;
		case GL_FLOAT_MAT2x4: return 2u * 4u;
		case GL_FLOAT_MAT3x2: return 3u * 2u;
		case GL_FLOAT_MAT3x4: return 3u * 4u;
		case GL_FLOAT_MAT4x2: return 4u * 2u;
		case GL_FLOAT_MAT4x3: return 4u * 3u;
		case GL_INT: return 1u;
		case GL_INT_VEC2: return 2u;
		case GL_INT_VEC3: return 3u;
		case GL_INT_VEC4: return 4u;
		case GL_UNSIGNED_INT: return 1u;
		case GL_UNSIGNED_INT_VEC2: 2u;
		case GL_UNSIGNED_INT_VEC3: 3u;
		case GL_UNSIGNED_INT_VEC4: 4u;
		case GL_DOUBLE: return 1u;
		case GL_DOUBLE_VEC2: return 2u;
		case GL_DOUBLE_VEC3: return 3u;
		case GL_DOUBLE_VEC4: return 4u;
		case GL_DOUBLE_MAT2: return 2u * 2u;
		case GL_DOUBLE_MAT3: return 3u * 3u;
		case GL_DOUBLE_MAT4: return 4u * 4u;
		case GL_DOUBLE_MAT2x3: return 2u * 3u;
		case GL_DOUBLE_MAT2x4: return 2u * 4u;
		case GL_DOUBLE_MAT3x2: return 3u * 2u;
		case GL_DOUBLE_MAT3x4: return 3u * 4u;
		case GL_DOUBLE_MAT4x2: return 4u * 2u;
		case GL_DOUBLE_MAT4x3: return 4u * 3u;
		}

		return 1u;
	}



	OpenGLShader::OpenGLShader(const ShaderSpecification& specification)
		: Shader(specification.ShaderName)
	{

		for (auto [domain, source] : specification.SourceFiles)
		{
			m_ShaderSources[domain] = LoadSourceFileFromFile(source);
		}

		Reload();
	}

	OpenGLShader::OpenGLShader(const std::string& shaderName, const std::unordered_map<ShaderDomain, std::string>& shaderSources)
		: Shader(shaderName), m_ShaderSources(shaderSources)
	{
		Reload();
	}

	OpenGLShader::~OpenGLShader()
	{
		if (m_ProgramID != 0u)
			glDeleteProgram(m_ProgramID);

		for (auto& shader : m_Shaders)
			glDeleteShader(shader);

	}

	auto OpenGLShader::Reload() -> void
	{
		CompileAndLink();
		FindUniforms();
		FindAttributes();
	}

	auto OpenGLShader::LoadSourceFileFromFile(const std::string& filepath) -> std::string
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

	auto OpenGLShader::CompileAndLink() -> void
	{
		for (auto& [domain, source] : m_ShaderSources)
		{
			std::string domainString = DomainToString(domain);
			LOG_CORE_INFO(" Shader: {}", domainString);

			GLuint shader = glCreateShader(ToNative(domain));

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

			m_Shaders.push_back(shader);
		}

		if (m_ProgramID != 0u)
			glDeleteProgram(m_ProgramID);

		m_ProgramID = glCreateProgram();

		for (auto& shader : m_Shaders)
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


		for (auto& shader : m_Shaders)
		{
			glDetachShader(m_ProgramID, shader);
		}

	}

	auto OpenGLShader::FindUniforms() -> void
	{
		if (!m_UniformInfos.empty())
			m_UniformInfos.clear();

		GLint uniformCount{ 0 };
		glGetProgramiv(m_ProgramID, GL_ACTIVE_UNIFORMS, &uniformCount);

		if (uniformCount == 0)
			return;

		GLint maxNameLength{ 0 };
		glGetProgramiv(m_ProgramID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);

		auto uniformName = CreateScope<char[]>(maxNameLength);

		GLsizei length{ 0 };
		GLsizei count{ 0 };
		GLenum type{ GL_NONE };

		for (auto i = 0; i < uniformCount; i++)
		{
			glGetActiveUniform(m_ProgramID, i, maxNameLength, &length, &count, &type, uniformName.get());

			ShaderUniformInfo uniformInfo{};
			uniformInfo.Location = glGetUniformLocation(m_ProgramID, uniformName.get());
			uniformInfo.Count = count;

			std::string name = uniformName.get();
			LOG_CORE_INFO(" - Uniform found: {}", name);
			//			LOG_CORE_INFO(" - Uniform found: {}", uniformName.get());

			m_UniformInfos.emplace(std::make_pair(std::string(uniformName.get(), length), uniformInfo));
		}
	}

	auto OpenGLShader::FindAttributes() -> void
	{
		if (!m_Layout.empty())
			m_Layout.clear();

		GLint attributeCount{ 0 };
		glGetProgramiv(m_ProgramID, GL_ACTIVE_ATTRIBUTES, &attributeCount);

		if (attributeCount == 0)
			return;

		GLint maxNameLength{ 0 };
		glGetProgramiv(m_ProgramID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxNameLength);

		auto attributeName = CreateScope<char[]>(maxNameLength);

		GLsizei length{ 0 };
		GLsizei size{ 0 };
		GLenum type{ GL_NONE };

		for (auto i = 0; i < attributeCount; i++)
		{
			glGetActiveAttrib(m_ProgramID, i, maxNameLength, &length, &size, &type, attributeName.get());

			auto location = glGetAttribLocation(m_ProgramID, attributeName.get());

			ShaderLayoutInfo layoutInfo{ };
			layoutInfo.Count = EnumCount(type);
			layoutInfo.Type = ToNative(type);
			layoutInfo.Size = EnumLength(type);

			uint32_t vertexBufferPosition{ 0 };

			if (type == GL_FLOAT_MAT4)
			{
				vertexBufferPosition = 1;
				layoutInfo.IsMatrix = true;
			}

			layoutInfo.VertexBufferPosition = vertexBufferPosition;

			m_Layout[location] = layoutInfo;

			std::string name = attributeName.get();
			LOG_CORE_INFO(" - Attribute found: {} @ location {}", name, location);
		}

	}

	auto OpenGLShader::Bind() const -> void
	{
		glUseProgram(m_ProgramID);
	}

	auto OpenGLShader::SetUniform(const std::string& uniformName, int32_t value) -> void
	{
		auto location = m_UniformInfos[uniformName].Location;
		glUniform1i(location, value);
	}

	auto OpenGLShader::SetUniform(const std::string& uniformName, const glm::vec3& value) -> void
	{
		auto location = m_UniformInfos[uniformName].Location;
		glUniform3fv(location, 1, glm::value_ptr(value));
	}

	auto OpenGLShader::SetUniform(const std::string& uniformName, const glm::vec4& value) -> void
	{
		auto location = m_UniformInfos[uniformName].Location;
		glUniform4fv(location, 1, glm::value_ptr(value));
	}

	auto OpenGLShader::SetUniform(const std::string& uniformName, const glm::mat4& value) -> void
	{
		auto location = m_UniformInfos[uniformName].Location;
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}




}
