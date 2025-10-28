#version 450 core

layout (location = 0) out vec4 o_Color;
layout (location = 1) out float o_Depth;

in vec2 v_TexCoord;
in vec3 v_Normal;

uniform sampler2D u_GrassTexture;
uniform sampler2D u_RockTexture;

struct DirectionalLight
{
	vec3 Direction;
	vec3 Radiance;
};

layout(binding = 2, std140) uniform DirectionalLightBuffer
{
	DirectionalLight DirLight;
};

void main()
{
	vec3 lightDirection = vec3(-0.3, 0.5, 0.75);
	vec3 negativeLightDirection = normalize(-DirLight.Direction);

	float diffuse = max(dot(normalize(v_Normal), negativeLightDirection), 0.0);
	vec3 diffuseColor = diffuse * DirLight.Radiance;

	vec4 tex = texture(u_GrassTexture, v_TexCoord);

	o_Color = tex * vec4(diffuseColor, 1.0);

	o_Depth = gl_FragCoord.z;
}
