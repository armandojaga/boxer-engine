#include "Mesh.h"
#include "Globals.h"
#include "GL/glew.h"

#include <filesystem>

#include "Application.h"
#include "modules/ModuleProgram.h"
#include "core/util/Yaml.h"

Mesh::Mesh(const char* file_path)
{
    Load(file_path);
    SetupMesh();
}

Mesh::~Mesh()
{
    for (auto vertex : vertices)
    {
        delete vertex;
    }
    for (auto texture : textures)
    {
        delete texture;
    }
}

void Mesh::Load(const char* mesh_data)
{
    BE_LOG("Loading Mesh: %s", mesh_data);
    YAML::Node mesh_node = YAML::LoadFile(mesh_data);

    for (auto it = mesh_node.begin(); it != mesh_node.end(); ++it)
    {
        if (it->first.as<std::string>()._Equal("id"))
        {
            id = it->second.as<std::string>().c_str();
        }

        if (it->first.as<std::string>()._Equal("material"))
        {
            material_id = it->second.as<std::string>().c_str();
        }

        if (it->first.as<std::string>()._Equal("min_point"))
        {
            min_point.x = it->second["x"].as<float>();
            min_point.y = it->second["y"].as<float>();
            min_point.z = it->second["z"].as<float>();
        }

        if (it->first.as<std::string>()._Equal("max_point"))
        {
            max_point.x = it->second["x"].as<float>();
            max_point.y = it->second["y"].as<float>();
            max_point.z = it->second["z"].as<float>();
        }
    }

    // We iterate throughout vertices as the number of indices must match
    // with normals and texture coordinates
    vertices.reserve(mesh_node["vertices"].size());
    for (int index = 0; index < mesh_node["vertices"].size(); ++index)
    {
        float3 position;
        YAML::Node node = mesh_node["vertices"][index];
        BoxerEngine::Yaml::ToFloat3(node, position);
        //node.reset(); // TODO: check if necessary

        float3 normal;
        node = mesh_node["normals"][index];
        BoxerEngine::Yaml::ToFloat3(node, normal);
        //node.reset(); // TODO: check if necessary

        float2 tex_coords;
        node = mesh_node["texture_coords"][index];
        BoxerEngine::Yaml::ToFloat2(node, tex_coords);

        vertices.push_back(new Vertex(position, normal, tex_coords));
    }

    indices.reserve(mesh_node["indices"].size() * 3);
    for (int i = 0; i < mesh_node["indices"].size(); ++i)
    {
        indices.push_back(mesh_node["indices"][i][0].as<int>());
        indices.push_back(mesh_node["indices"][i][1].as<int>());
        indices.push_back(mesh_node["indices"][i][2].as<int>());
    }

    // Go for the textures
    LoadTextureData(mesh_data, mesh_node["material"].as<std::string>().c_str());
}

void Mesh::LoadTextureData(const char* mesh_path, const char* material_id)
{
    std::filesystem::path meshes_path(mesh_path);
    std::filesystem::path library_path = meshes_path.parent_path();
    library_path.append(material_id);

    YAML::Node texture_node = YAML::LoadFile(library_path.string());

    textures.reserve(texture_node["texture"].size());
    for (auto texture : texture_node["texture"])
    {
        std::string path;
        std::string type;
        unsigned int opengl_id;

        if (texture["diffuse"].IsDefined())
        {
            path = texture["diffuse"]["texture_name"].as<std::string>();
            opengl_id = texture["diffuse"]["opengl_id"].as<unsigned int>();
            type = "texture_diffuse";
        }
        
        if (texture["specular"].IsDefined())
        {
            path = texture["specular"]["texture_name"].as<std::string>();
            opengl_id = texture["specular"]["opengl_id"].as<unsigned int>();
            type = "texture_specular";
        }

        textures.push_back(new Texture(opengl_id, type, path));
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
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        // activate proper Texture unit before binding
        // retrieve Texture number (the N in diffuse_TextureN)
        std::string number;
        std::string name = textures[i]->type;
        if (name == "texture_diffuse")
        {
            number = std::to_string(diffuseNr++);
        }
        else if (name == "texture_specular")
        {
            number = std::to_string(specularNr++);
        }
        App->program->SetUniform((name + number), static_cast<int>(i));
        glBindTexture(GL_TEXTURE_2D, textures[i]->id);
    }

    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}