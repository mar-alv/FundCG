#version 450

layout (location = 1) in vec3 color;
layout (location = 0) in vec3 position;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

out vec4 finalColor;

void main()
{
    finalColor = vec4(color, 1.0);
    gl_Position = projection * view * model * vec4(position, 1.0);
}
