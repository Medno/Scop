#version 410

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aColors;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float aAlphaTex;

out vec3 colors;
out vec2 TexCoord;
out float alphaTex;
void main()
{
  gl_Position = projection * view * model * vec4(position, 1.0);
  TexCoord = aTexCoord;
  alphaTex = aAlphaTex;
  colors = aColors;
}
