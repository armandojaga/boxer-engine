#pragma once
#include "Component.h"

#include <vector>
#include "core/rendering/BoundingBox.h"
#include "core/rendering/Model.h"

namespace BoxerEngine
{
    struct MeshData
    {
        MeshData(bool enable = true, bool has_texture = false, int type = 0)
            : enabled(enable)
              , texture_loaded(has_texture)
              , texture_type(type)
        {
        }

        bool enabled;
        bool texture_loaded;
        int texture_type;
        std::string texture_name;
    };

    class Entity;

    class MeshComponent final : public Component
    {
    public:
        inline static Type type = Type::MESH;

        explicit MeshComponent(Entity* entity);
        ~MeshComponent() override;

        void UpdateUI() override;
        void Update() override;
        [[nodiscard]] const char* GetName() const override;
        void Draw() override;

        [[nodiscard]] const char* GetModelPath() const;
        [[nodiscard]] const char* GetMeshTextureName(const int index) const { return meshes[index]->texture_name.c_str(); };
        [[nodiscard]] int GetMeshTextureType(const int index) const { return meshes[index]->texture_type; };
        [[nodiscard]] int GetMeshesCount() const { return meshes.size(); };

        void LoadModel(const char* path);
        void LoadTexture(const char* path, int mesh_index, int type);
        void EnableMesh(int index) { meshes[index]->enabled = true; }
        void DisableMesh(int index) { meshes[index]->enabled = false; }
        bool IsMeshEnabled(const int index) const { return meshes[index]->enabled; };
        bool IsMeshTextureLoaded(const int index) const { return meshes[index]->texture_loaded; };

    private:
        bool model_loaded = false;
        Model* model = nullptr;
        std::vector<MeshData*> meshes{};

        void DisplayLoadedUI();
        void DisplayNotLoadedUI();
        void AddTextureDisplay(int meshIndex);
        int TexturesTypesListBox();
    };
}
