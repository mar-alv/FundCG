#version 450

in vec4 finalColor;

out vec4 color;

void main()
{
    color = finalColor;

    bool isCubeWHite = color.x == 1.0 && color.y == 1.0 && color.z == 1.0;

    if (isCubeWHite) {
        color.a = 0.1;
    }
}
