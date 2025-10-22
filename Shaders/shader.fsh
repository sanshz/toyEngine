#version 330 core

out vec4 FragColor;

in vec4 posToColor;

void main()
{
  FragColor = posToColor;
}
