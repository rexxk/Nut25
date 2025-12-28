#include "Platform/OpenGL/OpenGLProgram.h"
#include "Platform/OpenGL/OpenGLUtils.h"

#include "Renderer/Shader.h"

#include "Core/Log.h"

#include <glm/gtc/type_ptr.hpp>


namespace Nut
{




	OpenGLProgram::OpenGLProgram(const std::string& name, const std::vector<std::string>& shaderList)
		: Program(name)
	{
		m_ProgramID = glCreateProgram();

		for (auto& shaderName : shaderList)
		{
			auto shader = ShaderLibrary::GetShader(shaderName);
			glAttachShader(m_ProgramID, shader->ID());
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


		for (auto& shaderName : shaderList)
		{
			auto shader = ShaderLibrary::GetShader(shaderName);
			glDetachShader(m_ProgramID, shader->ID());
		}

		FindUniforms();
		FindAttributes();
	}

	OpenGLProgram::~OpenGLProgram()
	{
		if (m_ProgramID != 0)
			glDeleteProgram(m_ProgramID);
	}

	auto OpenGLProgram::FindUniforms() -> void
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

	auto OpenGLProgram::FindAttributes() -> void
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

	auto OpenGLProgram::Bind() const -> void
	{
		glUseProgram(m_ProgramID);
	}

	auto OpenGLProgram::SetUniform(const std::string& uniformName, int32_t value) -> void
	{
		auto location = m_UniformInfos[uniformName].Location;
		glUniform1i(location, value);
	}

	auto OpenGLProgram::SetUniform(const std::string& uniformName, const glm::vec3& value) -> void
	{
		auto location = m_UniformInfos[uniformName].Location;
		glUniform3fv(location, 1, glm::value_ptr(value));
	}

	auto OpenGLProgram::SetUniform(const std::string& uniformName, const glm::vec4& value) -> void
	{
		auto location = m_UniformInfos[uniformName].Location;
		glUniform4fv(location, 1, glm::value_ptr(value));
	}

	auto OpenGLProgram::SetUniform(const std::string& uniformName, const glm::mat4& value) -> void
	{
		auto location = m_UniformInfos[uniformName].Location;
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

}
