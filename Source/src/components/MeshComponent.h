#pragma once
#include "Component.h"

#include <string>
#include <vector>

#include "Math/float3.h"
#include "Math/float2.h"
#include "../vendors/ImGuiFileDialog/ImGuiFileDialog.h"

#include "core/rendering/BoundingBox.h"
#include "core/rendering/Model.h"

namespace BoxerEngine
{
	struct MeshData
	{
		MeshData(bool enable = true, bool has_texture = false)
			: enabled(enable)
			, texture_loaded(has_texture)
		{}
		bool enabled;
		bool texture_loaded;
	};

class Entity;

	class MeshComponent final : public Component
	{
    public:
        inline static Type type = Type::MESH;

		explicit MeshComponent(Entity* parent);
		~MeshComponent() override;

        void UpdateUI() override;
        void Update() override;
        [[nodiscard]] const char* GetName() const override;

		void Draw();
		void Enable() { enabled = true; }
		void Disable() { enabled = false; }

    private:
		bool model_loaded = false;
		BoxerEngine::Model* Model = nullptr;
		std::vector<MeshData*> meshes{};

		void DisplayLoadedUI();
		void DisplayNotLoadedUI();
		void AddTextureDisplay(const int mesh_index);
		int TexturesTypesListBox();
	};
}