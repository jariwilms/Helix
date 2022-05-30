#version 460 core

in vec3 v_position;

out vec4 f_color;

void main()
{
	f_color = vec4(v_position * 0.5 + 0.5, 1.0);
}
