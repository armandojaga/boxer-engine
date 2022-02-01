#pragma once
#include "Component.h"

#include <vector>
#include "core/rendering/BoundingBox.h"
#include "core/rendering/Model.h"

namespace BoxerEngine
{
    struct MeshData
    {
        MeshData(bool enable = true, bool has_texture = false)
            : enabled(enable)
              , texture_loaded(has_texture)
        {
        }

        bool enabled;
        bool texture_loaded;
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

    private:
        bool model_loaded = false;
        Model* Model = nullptr;
        std::vector<MeshData*> meshes{};

        void DisplayLoadedUI();
        void DisplayNotLoadedUI();
        void AddTextureDisplay(int mesh_index);
        int TexturesTypesListBox();
    };
}
