@vertex
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

@fragment
#version 460 core

uniform vec3 u_baseColor;
uniform sampler2D u_albedo;

//uniform float u_metallicity;
//uniform float u_roughness;
uniform float u_opacity;

layout (location = 0) in vec2 				v_texCoord;

layout (location = 0) out vec4 				f_color;

void main()
{
	f_color = vec4(u_baseColor, 1.0) * texture(u_albedo, v_texCoord);
	//f_color = vec4(gl_fragCoord, 1.0);
	//f_color.a *= u_opacity;
}