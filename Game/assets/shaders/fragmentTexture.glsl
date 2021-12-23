#version 460 core

layout(early_fragment_tests) in;

/* Shader Outputs */
out vec4 color;

/* Shader Inputs */
in vec2 coords;

/* Uniforms */
/* Texture */
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;

uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

void main()
{
    color = texture2D(texture, coords);
}