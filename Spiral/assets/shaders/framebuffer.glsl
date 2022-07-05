@vertex
#version 460 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texCoord;

out vec2 v_texCoord;

void main()
{
	gl_Position = vec4(a_position, 1.0);
	
	v_texCoord = a_texCoord;
}

@fragment
#version 460 core

uniform sampler2D u_texture;

in vec2 v_texCoord;

out vec4 f_color;

void main()
{
	f_color = texture(u_texture, v_texCoord);
}
