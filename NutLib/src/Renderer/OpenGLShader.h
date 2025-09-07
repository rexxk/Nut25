#pragma once

#include "Core/Base.h"

#include <glad/glad.h>

#include <filesystem>
#include <string>
#include <string_view>
#include <unordered_map>


namespace Nut
{

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

		OpenGLShader(const std::filesystem::path& vertexShaderFile, const std::filesystem::path& framgentShaderPath);
		OpenGLShader(const std::string& shaderName, const std::unordered_map<Domain, std::string>& shaderSources);
		~OpenGLShader();

		auto Reload() -> void;

		auto Bind() const -> void;

		auto ID() const -> const GLuint { return m_ProgramID; }

		auto GetName() const -> std::string_view { return m_Name; }

	private:
		auto CompileAndLink() -> void;

	private:
		GLuint m_ProgramID{ -1u };

		std::string m_Name{};

		std::unordered_map<Domain, std::string> m_ShaderSources{};
	};

}

