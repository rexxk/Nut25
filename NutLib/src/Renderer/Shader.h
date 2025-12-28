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

	enum class ShaderDomain
	{
		Vertex,
		Fragment,
		Geometry,
		Compute,
	};


	struct ShaderSpecification
	{
		std::vector<std::pair<ShaderDomain, std::string>> SourceFiles;
		std::string ShaderName{};

		auto AddSourceFilePath(ShaderDomain domain, const std::string& filepath) -> void
		{
			SourceFiles.push_back(std::make_pair(domain, filepath));
		}
	};


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

	class Shader
	{
	public:
		static auto Load(const ShaderSpecification& specification) -> Ref<Shader>;

		Shader(const std::string& name);
		virtual ~Shader() = default;

		virtual auto Reload() -> void = 0;
		virtual auto Bind() const -> void = 0;

		auto GetName() const -> std::string;

		virtual auto GetLayout() const -> std::unordered_map<int32_t, ShaderLayoutInfo> const { return {}; }

		virtual auto SetUniform(const std::string& uniformName, int32_t value) -> void {}
		virtual auto SetUniform(const std::string& uniformName, const glm::vec3& value) -> void {}
		virtual auto SetUniform(const std::string& uniformName, const glm::vec4& value) -> void {}
		virtual auto SetUniform(const std::string& uniformName, const glm::mat4& value) -> void {}

	private:
		std::string m_Name{};
	};


	class ShaderLibrary
	{
	public:
		static auto Add(Ref<Shader> shader) -> void;
		static auto Delete(const std::string& name) -> void;

		static auto Get(const std::string& name) -> Ref<Shader>;

	};

}

