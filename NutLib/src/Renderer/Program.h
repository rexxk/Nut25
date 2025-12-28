#pragma once

#include "Core/Base.h"

#include <cstdint>
#include <string>
#include <vector>

#include <glm/glm.hpp>


namespace Nut
{


	struct ShaderLayoutInfo
	{
		int32_t Count{ 0 };
		int32_t Size{ 0 };
		uint32_t Type{ 0u };

		uint32_t VertexBufferPosition{ 0u };

		bool IsMatrix{ false };
	};


	class Program
	{
	public:
		static auto Link(const std::string& programName, const std::vector<std::string>& shaderList) -> Ref<Program>;

		Program() = default;
		Program(const std::string& name) : m_Name(name) {}
		Program(const Program& other) = delete;
		virtual ~Program() {}

		virtual auto Bind() const -> void = 0;

		virtual auto GetLayout() const -> std::unordered_map<int32_t, ShaderLayoutInfo> const { return {}; }

		virtual auto SetUniform(const std::string& uniformName, int32_t value) -> void {}
		virtual auto SetUniform(const std::string& uniformName, const glm::vec3& value) -> void {}
		virtual auto SetUniform(const std::string& uniformName, const glm::vec4& value) -> void {}
		virtual auto SetUniform(const std::string& uniformName, const glm::mat4& value) -> void {}

		auto GetName() -> std::string { return m_Name; }

	private:
		std::string m_Name{};
	};

}
