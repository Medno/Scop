#version 410

out vec4 FragColor;

in vec2 TexCoord;
in float alphaTex;

uniform sampler2D texture1;

void main()
{
	vec2 flipped_texcoord = vec2(TexCoord.x, 1.0 - TexCoord.y);

	FragColor = mix(texture(texture1, flipped_texcoord), vec4(1.0, 1.0, 1.0, 1.0), alphaTex);
}
