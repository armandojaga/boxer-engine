#pragma once
#include "Panel.h"

namespace BoxerEngine
{
    class InspectorPanel final : public Panel
    {
    public:
        InspectorPanel();
        ~InspectorPanel() override = default;

        void Update() override;

    private:
        Entity* currentEntity = nullptr;
    };
}
