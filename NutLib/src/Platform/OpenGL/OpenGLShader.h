#pragma once

#include "Renderer/Shader.h"


#include <filesystem>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

#include <glad/glad.h>


namespace Nut
{


	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& shaderName, const std::unordered_map<ShaderDomain, std::string>& shaderSources);
		OpenGLShader(ShaderDomain domain, const std::string& shaderName, const std::filesystem::path& filepath);
		OpenGLShader(const ShaderSpecification& specification);
		OpenGLShader(const OpenGLShader& other) = delete;
		virtual ~OpenGLShader();

		virtual auto Reload() -> void override;

		virtual auto ID() const -> const uint32_t override { return m_ShaderID; }


	private:
		auto Compile() -> void;
		auto FindUniforms() -> void;
		auto FindAttributes() -> void;

	private:
		GLuint m_ShaderID{ 0u };

		std::string m_ShaderSource{};
		ShaderDomain m_Domain{ ShaderDomain::Vertex };

	};


}
