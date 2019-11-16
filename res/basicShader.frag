#version 410

out vec4 FragColor;

in vec3 colors;
in vec2 TexCoord;
in float alphaTex;
in vec3 FragPos;
in vec3 normal;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform sampler2D texture1;
uniform vec3 viewPos;
uniform int enableLight;


void main()
{
	vec3 result;
	vec2 flipped_texcoord = vec2(TexCoord.x, 1.0 - TexCoord.y);

	if (enableLight == 1) {
		float ambientStrength = 0.1;
		vec3 ambient = ambientStrength * lightColor;

		vec3 norm = normalize(normal);
		vec3 lightDir = normalize(lightPos - FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * lightColor;

		float specularStrength = 0.5;
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		vec3 specular = specularStrength * spec * lightColor;

		result = (ambient + diffuse + specular) * colors;
	}
	else
		result = colors;

	if (alphaTex >= 1.0)
		FragColor = texture(texture1, flipped_texcoord);
	else if (alphaTex <= 0.0)
		FragColor = vec4(result, 1.0);
	else
		FragColor = mix(vec4(result, 1.0), texture(texture1, flipped_texcoord), alphaTex);
}
