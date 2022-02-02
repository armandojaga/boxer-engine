#include "core/bepch.h"
#include "Mesh.h"

#include "modules/ModuleProgram.h"
#include "core/util/Yaml.h"

using namespace BoxerEngine;

#define MAX_TEXTURES_COUNT 5

Mesh::Mesh(const char* file_path)
{
    textures.reserve(MAX_TEXTURES_COUNT);
    glBindTexture(GL_TEXTURE_2D, 0);
    Load(file_path);
    SetupMesh();
}

void Mesh::Load(const char* mesh_data)
{
    BE_LOG("Loading Mesh: %s", mesh_data);
    YAML::Node mesh_node = YAML::LoadFile(mesh_data);

    for (auto it = mesh_node.begin(); it != mesh_node.end(); ++it)
    {
        if (it->first.as<std::string>()._Equal(MESH_ID))
        {
            id = std::move(it->second.as<std::string>());
        }

        if (it->first.as<std::string>()._Equal(MIN_POINT))
        {
            min_point.x = it->second[NODE_X].as<float>();
            min_point.y = it->second[NODE_Y].as<float>();
            min_point.z = it->second[NODE_Z].as<float>();
        }

        if (it->first.as<std::string>()._Equal("max_point"))
        {
            max_point.x = it->second[NODE_X].as<float>();
            max_point.y = it->second[NODE_Y].as<float>();
            max_point.z = it->second[NODE_Z].as<float>();
        }
    }

    // We iterate throughout vertices as the number of indices must match
    // with normals and texture coordinates
    vertices.reserve(mesh_node[VERTICES_NODE].size());
    for (int index = 0; index < mesh_node[VERTICES_NODE].size(); ++index)
    {
        float3 position;
        YAML::Node node = mesh_node[VERTICES_NODE][index];
        Yaml::ToFloat3(node, position);

        float3 normal;
        node = mesh_node[NORMALS_NODE][index];
        Yaml::ToFloat3(node, normal);

        float2 tex_coords;
        node = mesh_node[TEXTURE_COORDS_NODE][index];
        Yaml::ToFloat2(node, tex_coords);

        vertices.emplace_back(Vertex(position, normal, tex_coords));
    }

    indices.reserve(mesh_node[INDICES_NODE].size() * 3);
    for (int i = 0; i < mesh_node[INDICES_NODE].size(); ++i)
    {
        indices.emplace_back(mesh_node[INDICES_NODE][i][0].as<int>());
        indices.emplace_back(mesh_node[INDICES_NODE][i][1].as<int>());
        indices.emplace_back(mesh_node[INDICES_NODE][i][2].as<int>());
    }
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
    glBindTexture(GL_TEXTURE_2D, 0);
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        // activate proper Texture unit before binding
        // retrieve Texture number (the N in diffuse_TextureN)
        std::string number;
        std::string name = textures[i].type;
        if (name._Equal("Diffuse"))
        {
            name = "texture_diffuse";
            number = std::to_string(diffuseNr++);
        }
        else if (name._Equal("Specular"))
        {
            name = "texture_specular";
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
}

void Mesh::SetTexture(unsigned int id, const char* type)
{
    for (int i = 0; i < textures.size(); ++i)
    {
        if (textures[i].type._Equal(type))
        {
            textures[i] = Texture(id, type);
            return;
        }
    }
    textures.emplace_back(id, type);
}
