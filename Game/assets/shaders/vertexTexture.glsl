#version 460 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 vertex_coords;

/* Shader Inputs */
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 texture_coords;

/* Shader Outputs */
out vec2 uv;
out vec3 normal;
out vec3 fragment_pos;

/* Uniforms */
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = proj * view * model * vec4(position, 1.0);
	
	/* INVERSE IS EXPENSIVE */
	/* For an efficient application you'll likely want to calculate the */
	/* normal matrix on the CPU and send it to the */
	/* shaders via a uniform before drawing */
	normal = mat3(transpose(inverse(model))) * normals; /* Normal Matrix: This conversion is done due to non-uniform scaling of the model, that could cause normals loss perpendicularity */
	fragment_pos = vec3(model * vec4(position, 1.0));
	uv = texture_coords;
}
