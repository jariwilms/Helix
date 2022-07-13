@vertex
#version 460 core

layout (std140) uniform Matrices
{
	mat4 u_view;
	mat4 u_projection;
};

layout (location = 0) in vec3 				a_position;
layout (location = 1) in vec4 				a_color;
layout (location = 2) in vec2 				a_texCoord;
layout (location = 3) in float 				a_texIndex;
layout (location = 4) in float 				a_texTiling;
layout (location = 5) in float 				a_entityId;

layout (location = 0) out vec4 				v_color;
layout (location = 1) out vec2 				v_texCoord;
layout (location = 2) out flat float 		v_texIndex;
layout (location = 3) out float 			v_texTiling;

void main()
{
	gl_Position = u_projection * u_view * vec4(a_position, 1.0);
	
	v_color = a_color;
	v_texCoord = a_texCoord;
	v_texIndex = a_texIndex;
	v_texTiling = a_texTiling;
}

@fragment
#version 460 core

layout (binding = 0) uniform sampler2D u_textures[32];

layout (location = 0) in vec4 				v_color;
layout (location = 1) in vec2 				v_texCoord;
layout (location = 2) in flat float 		v_texIndex;
layout (location = 3) in float 				v_texTiling;

layout (location = 0) out vec4 				f_color;

void main()
{
	f_color = v_color * texture(u_textures[int(v_texIndex)], v_texCoord * v_texTiling);
}
