#include "Mesh.h"
#include "Globals.h"
#include "GL/glew.h"

#include "Application.h"
#include "modules/ModuleProgram.h"

Mesh::Mesh(std::vector<Vertex> ver, std::vector<unsigned int> ind, std::vector<Texture> tex)
{
    vertices = ver;
    indices = ind;
    textures = tex;
    bounding_box = std::make_unique<BoxerEngine::BoundingBox>();

    SetupMesh();
}

Mesh::Mesh(std::vector<Vertex> ver, std::vector<unsigned int> ind, std::vector<Texture> tex, float3 minPoint, float3 maxPoint)
{
    vertices = ver;
    indices = ind;
    textures = tex;
    bounding_box = std::make_unique<BoxerEngine::BoundingBox>(BoxerEngine::BB_TYPE::AABB, minPoint, maxPoint);

    SetupMesh();
}

void Mesh::SetupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<void*>(nullptr));

    // Vertex texture coords
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));

    glBindVertexArray(0);
}

void Mesh::Draw() const
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        // activate proper Texture unit before binding
        // retrieve Texture number (the N in diffuse_TextureN)
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
        {
            number = std::to_string(diffuseNr++);
        }
        else if (name == "texture_specular")
        {
            number = std::to_string(specularNr++);
        }
        App->program->SetUniform((name + number), static_cast<int>(i));
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    bounding_box->Draw();
}
