#version 460 core

uniform sampler2D albedo;
//uniform sampler2D normal;

//uniform sampler2D diffuse;
//uniform sampler2D specular;

//uniform float metallicity;

layout (location = 0) in vec2 				v_texCoord;

layout (location = 0) out vec4 				f_color;

void main()
{
	f_color = texture(albedo, v_texCoord);
	//f_color = vec4(v_texCoord, 0.0, 1.0);
	//f_color = vec4(0.3, 0.5, 0.7, 1.0);
}