#version 410

out vec4 FragColor;

in vec2 TexCoord;
in float alphaTex;

uniform sampler2D texture1;

void main()
{
	FragColor = mix(texture(texture1, TexCoord), vec4(1.0, 1.0, 1.0, 1.0), alphaTex);
}
