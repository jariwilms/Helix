#version 460 core

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

layout (location = 0) in vec3 				a_position;
layout (location = 1) in vec3 				a_normal;
layout (location = 2) in vec3 				a_tangent;
layout (location = 3) in vec3 				a_bitangent;
layout (location = 4) in vec2 				a_texCoord;
layout (location = 5) in float 				a_entityId;

layout (location = 0) out vec2 				v_texCoord;
//layout (location = 1) out float 			v_texTiling;

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
	
	v_texCoord = a_texCoord;
	//v_texTiling = a_texTiling;
}
