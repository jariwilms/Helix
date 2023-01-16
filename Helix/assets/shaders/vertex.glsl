#version 460 core

out gl_PerVertex
{
  vec4 gl_Position;
  float gl_PointSize;
  float gl_ClipDistance[];
};

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec3 a_color;

layout(location = 0) out vec3 v_color;

void main()
{
	gl_Position = vec4(a_position, 0.0, 1.0);
	v_color = a_color;
}