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

layout (location = 0) out vec3				v_position;
layout (location = 1) out vec4				v_color;
layout (location = 2) out vec2				v_texCoord;
layout (location = 3) out flat float 		v_texIndex;

void main()
{
	vec4 worldPos = vec4(a_position, 1.0);
	v_position = worldPos.xyz;
	v_color = a_color;
	v_texCoord = a_texCoord;
	v_texIndex = a_texIndex;
	
	gl_Position = u_projection * u_view * worldPos;
}

@fragment
#version 460 core

layout (binding = 0) uniform sampler2D u_textures[32];

layout (location = 0) in vec3				v_position;
layout (location = 1) in vec4				v_color;
layout (location = 2) in vec2				v_texCoord;
layout (location = 3) in flat float 		v_texIndex;

layout (location = 0) out vec3 				g_position;
layout (location = 1) out vec3 				g_normal;
layout (location = 2) out vec4 				g_albedoSpec;

void main()
{
	g_position = v_position;
	g_normal = vec3(0.0, 0.0, 1.0);
	g_albedoSpec = texture(u_textures[int(v_texIndex)], v_texCoord);
}
