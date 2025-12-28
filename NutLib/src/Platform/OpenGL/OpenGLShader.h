#pragma once

#include "Renderer/Shader.h"


namespace Nut
{


	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& shaderName, const std::unordered_map<ShaderDomain, std::string>& shaderSources);
		OpenGLShader(const ShaderSpecification& specification);
		virtual ~OpenGLShader();

		virtual auto Reload() -> void override;

		virtual auto Bind() const -> void override;

		auto ID() const -> const GLuint { return m_ProgramID; }

		virtual auto GetLayout() const -> std::unordered_map<int32_t, ShaderLayoutInfo> const override { return m_Layout; }

		virtual auto SetUniform(const std::string& uniformName, int32_t value) -> void override;
		virtual auto SetUniform(const std::string& uniformName, const glm::vec3& value) -> void override;
		virtual auto SetUniform(const std::string& uniformName, const glm::vec4& value) -> void override;
		virtual auto SetUniform(const std::string& uniformName, const glm::mat4& value) -> void override;

	private:
		auto LoadSourceFileFromFile(const std::string& filepath) -> std::string;

		auto CompileAndLink() -> void;
		auto FindUniforms() -> void;
		auto FindAttributes() -> void;

	private:
		GLuint m_ProgramID{ 0u };

		std::unordered_map<ShaderDomain, std::string> m_ShaderSources{};
		std::unordered_map<std::string, ShaderUniformInfo> m_UniformInfos{};
		std::unordered_map<int32_t, ShaderLayoutInfo> m_Layout{};

		std::vector<GLuint> m_Shaders{};
	};

}
