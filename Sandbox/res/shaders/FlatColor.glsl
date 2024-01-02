#type vertex
#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;

out vec4 v_Color;

uniform vec4 u_ViewProjection;

void main()
{
	v_Color = a_Color;
	gl_Position = vec4(u_ViewProjection.xyz + a_Position.xyz, u_ViewProjection.a);
};

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;

void main()
{
	color = v_Color;
};
