#version 450

in vec4 finalColor;

out vec4 color;

void main()
{
    color = finalColor;
    color.a = 0.1;
}
