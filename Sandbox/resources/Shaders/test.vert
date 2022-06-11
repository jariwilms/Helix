#version 460 core

struct VertexData
{
	vec4 color;
	vec2 texCoord;
	float texIndex;
	float texTiling;
};

uniform mat4 u_view;
uniform mat4 u_projection;

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec4 a_color;
layout (location = 2) in vec2 a_texCoord;
layout (location = 3) in float a_texIndex;
layout (location = 4) in float a_texTiling;
layout (location = 5) in float a_entityId;

layout (location = 0) out VertexData v_output;

void main()
{
	gl_Position = u_projection * u_view * vec4(a_position, 1.0);
	
	v_output.color = a_color;
	v_output.texCoord = a_texCoord;
	v_output.texIndex = a_texIndex;
	v_output.texTiling = a_texTiling;
}
