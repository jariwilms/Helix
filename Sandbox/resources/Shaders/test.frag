#version 460 core

struct VertexData
{
	vec4 color;
	vec2 texCoord;
	float texIndex;
	float texTiling;
};

layout (binding = 0) uniform sampler2D u_textures[32];

layout (location = 0) in VertexData v_input;

layout (location = 0) out vec4 f_color;

void main()
{
	f_color = v_input.color * texture(u_textures[int(v_input.texIndex)], v_input.texCoord);
}