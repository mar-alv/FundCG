#version 450

in vec4 vertexColor;
in vec2 texCoord;

out vec4 color;

uniform sampler2D tex_buffer;
uniform vec2 offsets;

void main()
{
    color = texture(tex_buffer, texCoord + offsets);
}
