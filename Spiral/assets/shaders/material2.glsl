@vertex
#version 460 core

uniform mat4 u_model;

layout (location = 0) in vec3 				a_position;
layout (location = 1) in vec3 				a_normal;
layout (location = 2) in vec3 				a_tangent;
layout (location = 3) in vec3 				a_bitangent;
layout (location = 4) in vec2 				a_texCoord;
layout (location = 5) in float 				a_entityId;

layout (location = 0) out vec3				v_position;
layout (location = 1) out vec3 				v_normal;
layout (location = 2) out vec2 				v_texCoord;

void main()
{
	gl_Position = u_model * vec4(a_position, 1.0);
	
	v_position = u_model * vec4(a_position, 1.0);
	v_normal = a_normal;
	v_texCoord = a_texCoord;
}

@fragment
#version 460 core

uniform vec3 u_baseColor;
uniform sampler2D u_albedo;
uniform sampler2D u_specular;

layout (location = 0) in vec3				v_position;
layout (location = 1) in vec3 				v_normal;
layout (location = 2) in vec2 				v_texCoord;

layout (location = 0) out vec3 				g_position;
layout (location = 1) out vec3 				g_normal;
layout (location = 2) out vec4 				g_albedoSpec;

void main()
{
	g_position = v_position;
	g_normal = normalize(v_normal);
	g_albedoSpec.rgb = texture(u_albedo, v_texCoord).rgb;
	g_albedoSpec.a = texture(u_specular, v_texCoord).r;
}
