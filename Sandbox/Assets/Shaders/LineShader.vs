#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

layout(binding = 0, std140) uniform Camera
{
	mat4 ViewProjection;
};

out vec4 v_Color;

void main()
{
	gl_Position = ViewProjection * vec4(a_Position, 1.0);

	v_Color = a_Color;
}
