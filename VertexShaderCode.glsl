#version 420 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vertexColor;

uniform vec3 galaxycolor;
uniform mat4 trans;
uniform mat4 view;

out vec3 fragcol;

void main()
{
	vec4 pos = vec4(position, 1.0);
	gl_Position = view * trans * pos ;
	fragcol = vertexColor * galaxycolor;
}
