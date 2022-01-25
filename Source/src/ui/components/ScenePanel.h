#pragma once
#include "Panel.h"

namespace BoxerEngine
{
    class ScenePanel final : public Panel
    {
    public:
        ScenePanel();
        ~ScenePanel() override = default;

        void Update() override;
    };
}
