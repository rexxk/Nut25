#pragma once

#include "Renderer/Program.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>


namespace Nut
{

	struct ShaderUniformInfo
	{
		GLint Location{ -1 };
		GLsizei Count{ 0 };
	};


	class OpenGLProgram : public Program
	{
	public:
		OpenGLProgram(const std::string& name, const std::vector<std::string>& shaderList);
		~OpenGLProgram();

		auto ID() const -> uint32_t { return m_ProgramID; }

		auto Bind() const -> void;

		virtual auto GetLayout() const -> std::unordered_map<int32_t, ShaderLayoutInfo> const override { return m_Layout; }

		virtual auto SetUniform(const std::string& uniformName, int32_t value) -> void override;
		virtual auto SetUniform(const std::string& uniformName, const glm::vec3& value) -> void override;
		virtual auto SetUniform(const std::string& uniformName, const glm::vec4& value) -> void override;
		virtual auto SetUniform(const std::string& uniformName, const glm::mat4& value) -> void override;

	private:
		auto FindUniforms() -> void;
		auto FindAttributes() -> void;

	private:
		GLuint m_ProgramID{ 0 };

		std::unordered_map<std::string, ShaderUniformInfo> m_UniformInfos{};
		std::unordered_map<int32_t, ShaderLayoutInfo> m_Layout{};

	};

}
