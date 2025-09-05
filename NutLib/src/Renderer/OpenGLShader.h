#pragma once

#include "Core/Base.h"

#include <glad/glad.h>

#include <filesystem>
#include <string>
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
		auto LoadFromFile(const std::filesystem::path& vertexShaderFile, const std::filesystem::path& fragmentShaderPath) -> Ref<OpenGLShader>;
		auto LoadFlatShader() -> Ref<OpenGLShader>;

		OpenGLShader(const std::filesystem::path& vertexShaderFile, const std::filesystem::path& framgentShaderPath);
		OpenGLShader(const std::unordered_map<Domain, std::string>& shaderSources);

		auto ID() const -> const GLuint { return m_ProgramID; }

	private:
		GLuint m_ProgramID{ 0 };
	};

}

