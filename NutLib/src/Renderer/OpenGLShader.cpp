#include "Renderer/OpenGLShader.h"


#include "Core/Log.h"

#include <string>
#include <unordered_map>


namespace Nut
{


	static std::unordered_map<std::string, Ref<OpenGLShader>> s_Shaders{};


	auto DomainToString(OpenGLShader::Domain domain) -> std::string
	{
		switch (domain)
		{
			case OpenGLShader::Domain::Vertex: return "Vertex";
			case OpenGLShader::Domain::Fragment: return "Fragment";
			case OpenGLShader::Domain::Geometry: return "Geometry";
			case OpenGLShader::Domain::Compute: return "Compute";
		}

		return "unknown";
	}

	auto DomainToGLShader(OpenGLShader::Domain domain) -> GLuint
	{
		switch (domain)
		{
			case OpenGLShader::Domain::Vertex: return GL_VERTEX_SHADER;
			case OpenGLShader::Domain::Fragment: return GL_FRAGMENT_SHADER;
			case OpenGLShader::Domain::Geometry: return GL_GEOMETRY_SHADER;
			case OpenGLShader::Domain::Compute: return GL_COMPUTE_SHADER;
		}

		return GL_NONE;
	}

	auto EnumTypeToLength(GLenum type) -> uint32_t
	{
		switch (type)
		{
			case GL_FLOAT: return sizeof(GLfloat);
			case GL_FLOAT_VEC2: return 2 * sizeof(GLfloat);
			case GL_FLOAT_VEC3: return 3 * sizeof(GLfloat);
			case GL_FLOAT_VEC4: return 4 * sizeof(GLfloat);
			case GL_FLOAT_MAT2: return 2 * 2 * sizeof(GLfloat);
			case GL_FLOAT_MAT3: return 3 * 3 * sizeof(GLfloat);
			case GL_FLOAT_MAT4: return 4 * 4 * sizeof(GLfloat);
			case GL_FLOAT_MAT2x3: return 2 * 3 * sizeof(GLfloat);
			case GL_FLOAT_MAT2x4: return 2 * 4 * sizeof(GLfloat);
			case GL_FLOAT_MAT3x2: return 3 * 2 * sizeof(GLfloat);
			case GL_FLOAT_MAT3x4: return 3 * 4 * sizeof(GLfloat);
			case GL_FLOAT_MAT4x2: return 4 * 2 * sizeof(GLfloat);
			case GL_FLOAT_MAT4x3: return 4 * 3 * sizeof(GLfloat);
			case GL_INT: return sizeof(GLint);
			case GL_INT_VEC2: return 2 * sizeof(GLint);
			case GL_INT_VEC3: return 3 * sizeof(GLint);
			case GL_INT_VEC4: return 4 * sizeof(GLint);
			case GL_UNSIGNED_INT: return sizeof(GLuint);
			case GL_UNSIGNED_INT_VEC2: return 2 * sizeof(GLuint);
			case GL_UNSIGNED_INT_VEC3: return 3 * sizeof(GLuint);
			case GL_UNSIGNED_INT_VEC4: return 4 * sizeof(GLuint);
			case GL_DOUBLE: return sizeof(GLdouble);
			case GL_DOUBLE_VEC2: return 2 * sizeof(GLdouble);
			case GL_DOUBLE_VEC3: return 3 * sizeof(GLdouble);
			case GL_DOUBLE_VEC4: return 4 * sizeof(GLdouble);
			case GL_DOUBLE_MAT2: return 2 * 2 * sizeof(GLdouble);
			case GL_DOUBLE_MAT3: return 3 * 3 * sizeof(GLdouble);
			case GL_DOUBLE_MAT4: return 4 * 4 * sizeof(GLdouble);
			case GL_DOUBLE_MAT2x3: return 2 * 3 * sizeof(GLdouble);
			case GL_DOUBLE_MAT2x4: return 2 * 4 * sizeof(GLdouble);
			case GL_DOUBLE_MAT3x2: return 3 * 2 * sizeof(GLdouble);
			case GL_DOUBLE_MAT3x4: return 3 * 4 * sizeof(GLdouble);
			case GL_DOUBLE_MAT4x2: return 4 * 2 * sizeof(GLdouble);
			case GL_DOUBLE_MAT4x3: return 4 * 3 * sizeof(GLdouble);
		}

		return 4;
	}

	auto EnumTypeToGLType(GLenum type) -> GLenum
	{
		switch (type)
		{
			case GL_FLOAT: return GL_FLOAT;
			case GL_FLOAT_VEC2: return GL_FLOAT;
			case GL_FLOAT_VEC3: return GL_FLOAT;
			case GL_FLOAT_VEC4: return GL_FLOAT;
			case GL_FLOAT_MAT2: return GL_FLOAT;
			case GL_FLOAT_MAT3: return GL_FLOAT;
			case GL_FLOAT_MAT4: return GL_FLOAT;
			case GL_FLOAT_MAT2x3: return GL_FLOAT;
			case GL_FLOAT_MAT2x4: return GL_FLOAT;
			case GL_FLOAT_MAT3x2: return GL_FLOAT;
			case GL_FLOAT_MAT3x4: return GL_FLOAT;
			case GL_FLOAT_MAT4x2: return GL_FLOAT;
			case GL_FLOAT_MAT4x3: return GL_FLOAT;
			case GL_INT: return GL_INT;
			case GL_INT_VEC2: return GL_INT;
			case GL_INT_VEC3: return GL_INT;
			case GL_INT_VEC4: return GL_INT;
			case GL_UNSIGNED_INT: return GL_UNSIGNED_INT;
			case GL_UNSIGNED_INT_VEC2: GL_UNSIGNED_INT;
			case GL_UNSIGNED_INT_VEC3: GL_UNSIGNED_INT;
			case GL_UNSIGNED_INT_VEC4: GL_UNSIGNED_INT;
			case GL_DOUBLE: return GL_DOUBLE;
			case GL_DOUBLE_VEC2: return GL_DOUBLE;
			case GL_DOUBLE_VEC3: return GL_DOUBLE;
			case GL_DOUBLE_VEC4: return GL_DOUBLE;
			case GL_DOUBLE_MAT2: return GL_DOUBLE;
			case GL_DOUBLE_MAT3: return GL_DOUBLE;
			case GL_DOUBLE_MAT4: return GL_DOUBLE;
			case GL_DOUBLE_MAT2x3: return GL_DOUBLE;
			case GL_DOUBLE_MAT2x4: return GL_DOUBLE;
			case GL_DOUBLE_MAT3x2: return GL_DOUBLE;
			case GL_DOUBLE_MAT3x4: return GL_DOUBLE;
			case GL_DOUBLE_MAT4x2: return GL_DOUBLE;
			case GL_DOUBLE_MAT4x3: return GL_DOUBLE;
		}

		return GL_FLOAT;
	}

	auto EnumTypeToCount(GLenum type) -> GLuint
	{
		switch (type)
		{
			case GL_FLOAT: return 1u;
			case GL_FLOAT_VEC2: return 2u;
			case GL_FLOAT_VEC3: return 3u;
			case GL_FLOAT_VEC4: return 4u;
			case GL_FLOAT_MAT2: return 2u * 2u;
			case GL_FLOAT_MAT3: return 3u * 3u;
			case GL_FLOAT_MAT4: return 4u * 4u;
			case GL_FLOAT_MAT2x3: return 2u * 3u;
			case GL_FLOAT_MAT2x4: return 2u * 4u;
			case GL_FLOAT_MAT3x2: return 3u * 2u;
			case GL_FLOAT_MAT3x4: return 3u * 4u;
			case GL_FLOAT_MAT4x2: return 4u * 2u;
			case GL_FLOAT_MAT4x3: return 4u * 3u;
			case GL_INT: return 1u;
			case GL_INT_VEC2: return 2u;
			case GL_INT_VEC3: return 3u;
			case GL_INT_VEC4: return 4u;
			case GL_UNSIGNED_INT: return 1u;
			case GL_UNSIGNED_INT_VEC2: 2u;
			case GL_UNSIGNED_INT_VEC3: 3u;
			case GL_UNSIGNED_INT_VEC4: 4u;
			case GL_DOUBLE: return 1u;
			case GL_DOUBLE_VEC2: return 2u;
			case GL_DOUBLE_VEC3: return 3u;
			case GL_DOUBLE_VEC4: return 4u;
			case GL_DOUBLE_MAT2: return 2u * 2u;
			case GL_DOUBLE_MAT3: return 3u * 3u;
			case GL_DOUBLE_MAT4: return 4u * 4u;
			case GL_DOUBLE_MAT2x3: return 2u * 3u;
			case GL_DOUBLE_MAT2x4: return 2u * 4u;
			case GL_DOUBLE_MAT3x2: return 3u * 2u;
			case GL_DOUBLE_MAT3x4: return 3u * 4u;
			case GL_DOUBLE_MAT4x2: return 4u * 2u;
			case GL_DOUBLE_MAT4x3: return 4u * 3u;
		}

		return 1u;
	}

	std::unordered_map<OpenGLShader::Domain, std::string> s_FlatShaderSources{
		{
			OpenGLShader::Domain::Vertex,
			R"(
				#version 450 core

				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec3 a_Normal;
				layout(location = 2) in vec4 a_Color;

				out vec3 v_Normal;
				out vec4 v_Color;

				void main() 
				{
					gl_Position = vec4(a_Position, 1.0);
					v_Color = a_Color;
					v_Normal = a_Normal;
				}
			)"
		},
		{
			OpenGLShader::Domain::Fragment,
			R"(
				#version 450 core

				out vec4 o_Color;
				in vec3 v_Normal;
				in vec4 v_Color;

				void main()
				{
					vec3 normal = v_Normal;
					normal *= -1.0;
					o_Color = v_Color + vec4(normal, 1.0);
				}

			)"
		}
	};


	auto OpenGLShader::LoadFromFile(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentShaderPath) -> Ref<OpenGLShader>
	{
		return CreateRef<OpenGLShader>(vertexShaderPath, fragmentShaderPath);
	}

	auto OpenGLShader::LoadFlatShader() -> Ref<OpenGLShader>
	{
		return CreateRef<OpenGLShader>("FlatShader", s_FlatShaderSources);
	}


	OpenGLShader::OpenGLShader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentShaderPath)
	{

	}

	OpenGLShader::OpenGLShader(const std::string& shaderName, const std::unordered_map<Domain, std::string>& shaderSources)
		: m_ShaderSources(shaderSources), m_Name(shaderName)
	{
		LOG_CORE_INFO("Compiling shader: {}", shaderName);

		Reload();
	}

	OpenGLShader::~OpenGLShader()
	{
		if (m_ProgramID != 0u)
			glDeleteProgram(m_ProgramID);
	}

	auto OpenGLShader::Reload() -> void
	{
		CompileAndLink();
		FindUniforms();
		FindAttributes();
	}

	auto OpenGLShader::CompileAndLink() -> void
	{
		std::vector<GLuint> shaders{};

		for (auto &[domain, source] : m_ShaderSources)
		{
			std::string domainString = DomainToString(domain);
			LOG_CORE_INFO(" Shader: {}", domainString);
	
			GLuint shader = glCreateShader(DomainToGLShader(domain));

			const GLchar* glSource = source.data();
			GLint sourceLength = static_cast<GLint>(source.size());

			glShaderSource(shader, 1u, &glSource, &sourceLength);
			glCompileShader(shader);

			GLint status{};
			glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

			if (status == GL_FALSE)
			{
				GLint infoLogLength{};
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

				std::string infoLog;
				infoLog.resize(static_cast<size_t>(infoLogLength));
				glGetShaderInfoLog(shader, infoLogLength, &infoLogLength, infoLog.data());

				LOG_CORE_ERROR("Shader error:\n{}", infoLog);

				return;
			}

			shaders.push_back(shader);
		}

		if (m_ProgramID != 0u)
			glDeleteProgram(m_ProgramID);

		m_ProgramID = glCreateProgram();

		for (auto& shader : shaders)
		{
			glAttachShader(m_ProgramID, shader);
		}

		glLinkProgram(m_ProgramID);

		GLint linkStatus{};
		glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &linkStatus);

		if (linkStatus == GL_FALSE)
		{
			GLint infoLogLength{};
			glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);

			std::string infoLog;
			infoLog.resize(static_cast<size_t>(infoLogLength));
			glGetProgramInfoLog(m_ProgramID, infoLogLength, &infoLogLength, infoLog.data());

			LOG_CORE_ERROR("Link error:\n{}", infoLog);
		}


		for (auto& shader : shaders)
		{
			glDeleteShader(shader);
		}

	}

	auto OpenGLShader::FindUniforms() -> void
	{
		if (!m_UniformInfos.empty())
			m_UniformInfos.clear();

		GLint uniformCount{ 0 };
		glGetProgramiv(m_ProgramID, GL_ACTIVE_UNIFORMS, &uniformCount);

		if (uniformCount == 0)
			return;

		GLint maxNameLength{ 0 };
		glGetProgramiv(m_ProgramID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);

		auto uniformName = CreateScope<char[]>(maxNameLength);

		GLsizei length{ 0 };
		GLsizei count{ 0 };
		GLenum type{ GL_NONE };

		for (auto i = 0; i < uniformCount; i++)
		{
			glGetActiveUniform(m_ProgramID, i, maxNameLength, &length, &count, &type, uniformName.get());

			ShaderUniformInfo uniformInfo{};
			uniformInfo.Location = glGetUniformLocation(m_ProgramID, uniformName.get());
			uniformInfo.Count = count;

			std::string name = uniformName.get();
			LOG_CORE_INFO(" - Uniform found: {}", name);
//			LOG_CORE_INFO(" - Uniform found: {}", uniformName.get());

			m_UniformInfos.emplace(std::make_pair(std::string(uniformName.get(), length), uniformInfo));
		}
	}
	
	auto OpenGLShader::FindAttributes() -> void
	{
		if (!m_Layout.empty())
			m_Layout.clear();

		GLint attributeCount{ 0 };
		glGetProgramiv(m_ProgramID, GL_ACTIVE_ATTRIBUTES, &attributeCount);

		if (attributeCount == 0)
			return;

		GLint maxNameLength{ 0 };
		glGetProgramiv(m_ProgramID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxNameLength);

		auto attributeName = CreateScope<char[]>(maxNameLength);

		GLsizei length{ 0 };
		GLsizei size{ 0 };
		GLenum type{ GL_NONE };

		for (auto i = 0; i < attributeCount; i++)
		{
			glGetActiveAttrib(m_ProgramID, i, maxNameLength, &length, &size, &type, attributeName.get());

			auto location = glGetAttribLocation(m_ProgramID, attributeName.get());

			ShaderLayoutInfo layoutInfo{ };
			layoutInfo.Count = EnumTypeToCount(type);
			layoutInfo.Type = EnumTypeToGLType(type);
			layoutInfo.Size = EnumTypeToLength(type);

			m_Layout[location] = layoutInfo;

			std::string name = attributeName.get();
			LOG_CORE_INFO(" - Attribute found: {} @ location {}", name, location);
		}

	}

	auto OpenGLShader::Bind() const -> void
	{
		glUseProgram(m_ProgramID);
	}

	auto OpenGLShader::ReleaseBinding() -> void
	{
		glUseProgram(0u);
	}




	auto ShaderLibrary::Add(Ref<OpenGLShader> shader) -> void
	{
		if (!s_Shaders.contains(shader->GetName()))
		{
			s_Shaders[shader->GetName()] = shader;
		}
	}

	auto ShaderLibrary::Delete(const std::string& name) -> void
	{
		if (s_Shaders.contains(name))
		{
			s_Shaders.erase(name);
		}
	}

	auto ShaderLibrary::Get(const std::string& name) -> Ref<OpenGLShader>
	{
		if (s_Shaders.contains(name))
			return s_Shaders[name];

		return nullptr;
	}

}
