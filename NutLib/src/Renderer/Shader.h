#pragma once

#include "Core/Base.h"
#include "Renderer/Program.h"

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


	class Shader
	{
	public:
		static auto Load(const ShaderSpecification& specification) -> Ref<Shader>;
		static auto Load(ShaderDomain domain, const std::string& shaderName, const std::filesystem::path& filepath) -> Ref<Shader>;

		Shader(const std::string& name);
		virtual ~Shader() = default;

		virtual auto Reload() -> void = 0;
		virtual auto ID() const -> const uint32_t = 0;

		auto GetName() const -> std::string;


	private:
		std::string m_Name{};
	};


	class ShaderLibrary
	{
	public:
		static auto Add(Ref<Shader> shader) -> void;
		static auto Add(Ref<Program> program) -> void;
		static auto Delete(const std::string& name) -> void;

		static auto GetShader(const std::string& name) -> Ref<Shader>;
		static auto GetProgram(const std::string& name) -> Ref<Program>;
	};

}

