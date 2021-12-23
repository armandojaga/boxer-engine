#include "Mesh_A.h"
#include "Globals.h"
#include "GL/glew.h"

#include "Application.h"
#include "modules/ModuleProgram.h"

Mesh_A::Mesh_A(std::vector<Vertex_A> vertices, std::vector<unsigned int> indices, std::vector<Texture_A> textures)
{
    Vertices = vertices;
    Indices = indices;
    Textures = textures;

    SetupMesh();
}

void Mesh_A::SetupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex_A), &Vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int),
        &Indices[0], GL_STATIC_DRAW);

    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_A), (void*)0);

    // Vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_A), (void*)offsetof(Vertex_A, Normal));

    // Vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex_A), (void*)offsetof(Vertex_A, TexCoords));

    glBindVertexArray(0);
}

void Mesh_A::Draw()
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for (unsigned int i = 0; i < Textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        // activate proper Texture unit before binding
        // retrieve Texture number (the N in diffuse_TextureN)
        std::string number;
        std::string name = Textures[i].Type;
        if (name == "Texture_A_diffuse")
        {
            number = std::to_string(diffuseNr++);
        }
        else if (name == "Texture_A_specular")
        {
            number = std::to_string(specularNr++);
        }
        App->program->SetUniform((name + number), (int)i);
        glBindTexture(GL_TEXTURE_2D, Textures[i].Id);
    }
    glActiveTexture(GL_TEXTURE0);
    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}