#pragma once
#include "Component.h"

#include <string>
#include <vector>

#include "Math/float3.h"
#include "Math/float2.h"

#include "core/rendering/BoundingBox.h"
#include "core/rendering/Model.h"

namespace BoxerEngine
{
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
    private:
		bool loaded = false;
		BoxerEngine::Model* Model = nullptr;

		void DisplayLoadedUI();
		void DisplayNotLoadedUI();
	};
}