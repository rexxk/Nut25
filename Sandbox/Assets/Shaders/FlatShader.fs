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
//	vec3 negativeLightDirection = normalize(-lightDirection);
	vec3 negativeLightDirection = normalize(-DirLight.Direction);

	float diffuse = max(dot(normalize(v_Normal), negativeLightDirection), 0.0);
//	vec3 diffuseColor = diffuse * vec3(1.0, 1.0, 1.0);
	vec3 diffuseColor = diffuse * DirLight.Radiance;

//	vec3 normal = v_Normal;
//	normal *= -1.0;

	vec4 tex = texture(u_Texture, v_TexCoord);

//	o_Color = tex * vec4(diffuseColor, 1.0);
	o_Color = tex * normalize((v_Color * vec4(diffuseColor, 1.0)));
//	o_Color = tex + v_Color * vec4(normal, 1.0);
	o_Depth = gl_FragCoord.z;
}
