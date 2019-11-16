#version 410

out vec4 FragColor;

in vec3 colors;
in vec2 TexCoord;
in float alphaTex;

uniform vec3 lightColor;
uniform sampler2D texture1;

void main()
{
	vec2 flipped_texcoord = vec2(TexCoord.x, 1.0 - TexCoord.y);

	if (alphaTex >= 1.0)
		FragColor = texture(texture1, flipped_texcoord);
	else if (alphaTex <= 0.0)
		FragColor = vec4(colors, 1.0);
	else
		FragColor = mix(vec4(colors, 1.0), texture(texture1, flipped_texcoord), alphaTex);
}
