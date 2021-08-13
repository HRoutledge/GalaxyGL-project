#version 420 core

out vec4 outcol;
in vec3 fragcol;

void main()
{
	outcol = vec4(fragcol,1.0f);
}
