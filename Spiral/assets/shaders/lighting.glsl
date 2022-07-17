@vertex
#version 460 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texCoord;

layout (location = 0) out vec2 v_texCoord;

void main()
{
	gl_Position = vec4(a_position, 1.0);
	v_texCoord = a_texCoord;
}

@fragment
#version 460 core

struct Light 
{
    vec3 position;
    vec3 color;
    
    float linear;
    float quadratic;
    float radius;
};

uniform sampler2D g_position;
uniform sampler2D g_normal;
uniform sampler2D g_albedoSpec;

uniform Light light;
uniform vec3 viewPos;

layout (location = 0) in vec2 v_texCoord;

layout (location = 0) out vec4 f_color;

void main()
{
    vec3 FragPos = texture(g_position, v_texCoord).rgb;
    vec3 Normal = texture(g_normal, v_texCoord).rgb;
    vec3 Diffuse = texture(g_albedoSpec, v_texCoord).rgb;
    float Specular = texture(g_albedoSpec, v_texCoord).a;
    
    vec3 lighting = Diffuse * 0.1;
    vec3 viewDir = normalize(viewPos - FragPos);
	
	float distance = length(light.position - FragPos);
	
	if(distance < light.radius)
	{
		//diffuse
		vec3 lightDir = normalize(light.position - FragPos);
		vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * light.color;
		
		//specular
		vec3 halfwayDir = normalize(lightDir + viewDir);  
		float spec = pow(max(dot(Normal, halfwayDir), 0.0), 16.0);
		vec3 specular = light.color * spec * Specular;
		
		//attenuation
		float attenuation = 1.0 / (1.0 + light.linear * distance + light.quadratic * distance * distance);
		diffuse *= attenuation;
		specular *= attenuation;
		lighting += diffuse + specular;
	}
	
    f_color = vec4(lighting, 1.0);
}