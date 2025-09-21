#pragma once

#include "Core/Base.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <filesystem>
#include <string>
#include <string_view>
#include <unordered_map>


namespace Nut
{



	struct ShaderUniformInfo
	{
		GLint Location{ -1 };
		GLsizei Count{ 0 };
	};

	struct ShaderLayoutInfo
	{
		GLsizei Count{ 0 };
		GLsizei Size{ 0 };
		GLenum Type{ GL_NONE };

		uint32_t VertexBufferPosition{ 0 };

		bool IsMatrix{ false };
	};

	class OpenGLShader
	{
	public:
		enum class Domain
		{
			Vertex, 
			Fragment,
			Geometry,
			Compute,
		};

	public:
		static auto LoadFromFile(const std::filesystem::path& vertexShaderFile, const std::filesystem::path& fragmentShaderPath) -> Ref<OpenGLShader>;
		static auto LoadFlatShader() -> Ref<OpenGLShader>;
		static auto LoadCompositionShader() -> Ref<OpenGLShader>;

		OpenGLShader(const std::filesystem::path& vertexShaderFile, const std::filesystem::path& framgentShaderPath);
		OpenGLShader(const std::string& shaderName, const std::unordered_map<Domain, std::string>& shaderSources);
		~OpenGLShader();

		auto Reload() -> void;

		auto Bind() const -> void;

		auto ID() const -> const GLuint { return m_ProgramID; }

		auto GetName() const -> std::string { return m_Name; }
		auto GetLayout() const -> std::unordered_map<GLint, ShaderLayoutInfo> const { return m_Layout; }

		auto SetUniform(const std::string& uniformName, int32_t value) -> void;
		auto SetUniform(const std::string& uniformName, const glm::vec3& value) -> void;
		auto SetUniform(const std::string& uniformName, const glm::vec4& value) -> void;
		auto SetUniform(const std::string& uniformName, const glm::mat4& value) -> void;

		static auto ReleaseBinding() -> void;

	private:
		auto CompileAndLink() -> void;
		auto FindUniforms() -> void;
		auto FindAttributes() -> void;

	private:
		GLuint m_ProgramID{ 0u };

		std::string m_Name{};

		std::unordered_map<Domain, std::string> m_ShaderSources{};
		std::unordered_map<std::string, ShaderUniformInfo> m_UniformInfos{};
		std::unordered_map<GLint, ShaderLayoutInfo> m_Layout{};

		std::vector<GLuint> m_Shaders{};
	};


	class ShaderLibrary
	{
	public:
		static auto Add(Ref<OpenGLShader> shader) -> void;
		static auto Delete(const std::string& name) -> void;

		static auto Get(const std::string& name) -> Ref<OpenGLShader>;

	};

}

