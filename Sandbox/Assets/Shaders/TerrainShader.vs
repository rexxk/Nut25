#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normal;
layout(location = 3) in vec4 a_Color;

layout(binding = 0, std140) uniform Camera
{
	mat4 ViewProjection;
};

layout(binding = 1, std140) uniform Transform
{
	mat4 TransformMatrix;
};

out vec2 v_TexCoord;
out vec3 v_Normal;
out vec4 v_Color;

void main() 
{
	gl_Position = ViewProjection * TransformMatrix * vec4(a_Position, 1.0);

	v_TexCoord = a_TexCoord;
	v_Color = a_Color;
	v_Normal = mat3(TransformMatrix) * a_Normal;
}
