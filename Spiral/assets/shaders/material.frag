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
	f_color.a *= u_opacity;
}