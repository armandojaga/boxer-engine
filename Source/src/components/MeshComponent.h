#pragma once
#include "Component.h"

#include <string>
#include <vector>
#include "Math/float3.h"
#include "Math/float2.h"
#include "core/rendering/BoundingBox.h"

namespace BoxerEngine
{
    struct Vertex
    {
        float3 position;
        float3 normal;
        float2 tex_coords;
    };

    struct Texture
    {
        unsigned int id{};
        std::string type;
        std::string path;
    };

    class Entity;

	class MeshComponent final : public Component
	{
    public:
        inline static Type type = Type::MESH;

		explicit MeshComponent(Entity* parent);
		~MeshComponent() override = default;

        void UpdateUI() override;
        [[nodiscard]] const char* GetName() const override;

    private:
        // mesh data
        std::vector<Vertex*> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture*> textures;
        std::unique_ptr<BoxerEngine::BoundingBox> bounding_box;

        //  render data
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;

        void SetupMesh();
	};


}

