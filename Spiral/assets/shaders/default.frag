#version 460 core

layout (binding = 0) uniform sampler2D u_textures[32];

layout (location = 0) in vec4 				v_color ;
layout (location = 1) in vec2 				v_texCoord;
layout (location = 2) in flat float 		v_texIndex;
layout (location = 3) in float 				v_texTiling;

layout (location = 0) out vec4 				f_color;

void main()
{
	f_color = v_color * texture(u_textures[int(v_texIndex)], v_texCoord * v_texTiling);
}