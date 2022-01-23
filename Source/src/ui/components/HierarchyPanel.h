#pragma once
#include "Panel.h"
#include "core/Entity.h"

namespace BoxerEngine
{
    class HierarchyPanel final : public Panel
    {
    public:
        HierarchyPanel();
        ~HierarchyPanel() override = default;

        void Update() override;

        void CreateEmptyEntity();
        void UpdateHierarchyTree(Entity* entity);
    };
}
