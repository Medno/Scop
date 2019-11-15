#version 410

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

in vec3 colors;
in vec2 TexCoord;
in float alphaTex;

void main()
{
	FragColor = vec4(lightColor * objectColor, 1.0);
}
