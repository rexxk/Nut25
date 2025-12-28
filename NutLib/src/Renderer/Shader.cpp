#include "Renderer/Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include "Renderer/RendererContext.h"

#include "Core/Log.h"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <string>
#include <unordered_map>


namespace Nut
{


	static std::unordered_map<std::string, Ref<Shader>> s_Shaders{};
	static std::unordered_map<std::string, Ref<Program>> s_Programs{};



	std::unordered_map<ShaderDomain, std::string> s_FlatShaderSources{
		{
			ShaderDomain::Vertex,
			R"(
				#version 450 core

				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec2 a_TexCoord;
				layout(location = 2) in vec3 a_Normal;
				layout(location = 3) in vec4 a_Color;
				layout(location = 4) in mat4 a_InstanceMatrix;

				layout(binding = 0, std140) uniform Camera
				{
					mat4 ViewProjection;
				};

				out vec2 v_TexCoord;
				out vec3 v_Normal;
				out vec4 v_Color;

				void main() 
				{
					gl_Position = ViewProjection * a_InstanceMatrix * vec4(a_Position, 1.0);

					v_TexCoord = a_TexCoord;
					v_Color = a_Color;
					v_Normal = mat3(a_InstanceMatrix) * a_Normal;
				}
			)"
		},
		{
			ShaderDomain::Fragment,
			R"(
				#version 450 core

				layout (location = 0) out vec4 o_Color;
				layout (location = 1) out float o_Depth;
				in vec2 v_TexCoord;
				in vec3 v_Normal;
				in vec4 v_Color;

				uniform sampler2D u_Texture;

				struct DirectionalLight
				{
					vec3 Direction;
					vec3 Radiance;
				};

				layout(binding = 1, std140) uniform DirectionalLightBuffer
				{
					DirectionalLight DirLight;
				};

				void main()
				{
					vec3 lightDirection = vec3(-0.3, 0.5, 0.75);
//					vec3 negativeLightDirection = normalize(-lightDirection);
					vec3 negativeLightDirection = normalize(-DirLight.Direction);

					float diffuse = max(dot(normalize(v_Normal), negativeLightDirection), 0.0);
//					vec3 diffuseColor = diffuse * vec3(1.0, 1.0, 1.0);
					vec3 diffuseColor = diffuse * DirLight.Radiance;

//					vec3 normal = v_Normal;
//					normal *= -1.0;

					vec4 tex = texture(u_Texture, v_TexCoord);

//					o_Color = tex * vec4(diffuseColor, 1.0);
					o_Color = tex * normalize((v_Color * vec4(diffuseColor, 1.0)));
//					o_Color = tex + v_Color * vec4(normal, 1.0);
					o_Depth = gl_FragCoord.z;
				}

			)"
		}
	};

	std::unordered_map<ShaderDomain, std::string> s_CompositionShaderSources{
	{
		ShaderDomain::Vertex,
		R"(
				#version 450 core

				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec2 a_TexCoord;

				out vec2 v_TexCoord;

				void main() 
				{
					gl_Position = vec4(a_Position, 1.0);
					v_TexCoord = a_TexCoord;
				}
			)"
		},
		{
			ShaderDomain::Fragment,
			R"(
				#version 450 core

				layout (location = 0) out vec4 o_Color;

				in vec2 v_TexCoord;

				uniform sampler2D u_Texture;

				void main()
				{
					o_Color = texture(u_Texture, v_TexCoord);
				}

			)"
		}
	};


	auto Shader::Load(const ShaderSpecification& specification) -> Ref<Shader>
	{
		switch (RendererContext::API())
		{
			case RendererAPI::OpenGL: return CreateRef<OpenGLShader>(specification);
			case RendererAPI::Vulkan: return nullptr;
		}

		return nullptr;
//		return CreateRef<OpenGLShader>(specification);
	}

	auto Shader::Load(ShaderDomain domain, const std::string& shaderName, const std::filesystem::path& filepath) -> Ref<Shader>
	{
		switch (RendererContext::API())
		{
			case RendererAPI::OpenGL: return CreateRef<OpenGLShader>(domain, shaderName, filepath);
			case RendererAPI::Vulkan: return nullptr;
		}

		return nullptr;
	}


	Shader::Shader(const std::string& name)
		: m_Name(name)
	{
		LOG_CORE_INFO("Compiling shader: {}", m_Name);
	}

	auto Shader::GetName() const -> std::string
	{
		return m_Name;
	}


	auto ShaderLibrary::Add(Ref<Shader> shader) -> void
	{
		if (!s_Shaders.contains(shader->GetName()))
		{
			s_Shaders[shader->GetName()] = shader;
		}
	}

	auto ShaderLibrary::Add(Ref<Program> program) -> void
	{
		if (!s_Programs.contains(program->GetName()))
		{
			s_Programs[program->GetName()] = program;
		}
	}

	auto ShaderLibrary::Delete(const std::string& name) -> void
	{
		if (s_Shaders.contains(name))
		{
			s_Shaders.erase(name);
		}
	}

	auto ShaderLibrary::GetShader(const std::string& name) -> Ref<Shader>
	{
		if (s_Shaders.contains(name))
			return s_Shaders[name];

		return nullptr;
	}

	auto ShaderLibrary::GetProgram(const std::string& name) -> Ref<Program>
	{
		if (s_Programs.contains(name))
			return s_Programs[name];

		return nullptr;
	}

}
