#version 460 core

layout(early_fragment_tests) in;

/* Shader Outputs */
out vec4 color;

/* Shader Inputs */
in vec2 coords;

/* Uniforms */
/* Texture */
uniform sampler2D texture;

void main()
{
    color = texture2D(texture, coords);
}