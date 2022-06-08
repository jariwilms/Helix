#version 460 core

struct VertexOutput
{
	vec4 color;
	vec2 texCoord;
	float texIndex;
	float texTiling;
};

layout (binding = 0) uniform sampler2D u_textures[32];

layout (location = 0) in VertexOutput v_input;

layout (location = 0) out vec4 f_color;

void main()
{
	f_color = vec4(1.0, 0.0, 1.0, 1.0);
}