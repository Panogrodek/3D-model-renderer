#type vertex
#version 330 core

layout (location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;

void main()
{
	gl_Position = u_ViewProjection * vec4(a_Position.xyz, 1.0);
};

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

void main()
{
	color = vec4(1.0,1.0,1.0,1.0);
};
