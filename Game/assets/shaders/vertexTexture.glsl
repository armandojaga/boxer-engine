#version 460 core

/* Shader Inputs */
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 vertex_coords;

out vec2 coords;

/* Uniforms */
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = projection * view * model * vec4(vertex, 1.0);
    coords = vertex_coords;
}
