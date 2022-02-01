#pragma once
#include "Panel.h"

namespace BoxerEngine
{
    class ScenePanel final : public Panel
    {
    public:
        ScenePanel();
        ~ScenePanel() override = default;

        void UpdateGizmoType();
        void Update() override;
    private:
        mutable Entity* active_entity = nullptr;
        int guizmo_operation = -1;
    };
}
