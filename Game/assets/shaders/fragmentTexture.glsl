#version 460 core

layout(early_fragment_tests) in;

out vec4 color;

in vec2 coords;

uniform sampler2D texture;

void main()
{
    color = texture2D(texture, coords);
}
