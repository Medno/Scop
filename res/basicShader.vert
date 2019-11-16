#version 410

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aColors;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float aAlphaTex;
uniform int enableLight;

out vec3 normal;
out vec3 colors;
out vec2 TexCoord;
out float alphaTex;
out vec3 FragPos;
void main()
{
  gl_Position = projection * view * model * vec4(position, 1.0);
  TexCoord = aTexCoord;
  alphaTex = aAlphaTex;
  colors = aColors;
  if (enableLight == 1)
  {
	  FragPos = vec3(model * vec4(position, 1.0));
	  normal = mat3(transpose(inverse(model))) * aNormal;
  }
}
