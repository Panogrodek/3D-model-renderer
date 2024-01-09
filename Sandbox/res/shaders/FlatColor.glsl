#type vertex
#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
uniform vec3 u_LightDir;

out vec3 v_Normal;
out vec3 v_LightDir;
out vec3 v_FragPos;

void main()
{
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position.xyz, 1.0);
	v_Normal = a_Normal;
	v_LightDir = u_LightDir;
	v_FragPos = vec3(u_Transform * vec4(a_Position,1.0));
};

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Normal;
in vec3 v_LightDir;
in vec3 v_FragPos;

void main()
{
	vec3 norm = normalize(v_Normal);
	vec3 dir = normalize(v_LightDir - v_FragPos);
	float diff = max(dot(norm,dir),0.0);
	vec3 light = diff * vec3(1.0,1.0,1.0);
	//color = vec4(light.xyz,1.0);
	color = vec4(1.0);
};
