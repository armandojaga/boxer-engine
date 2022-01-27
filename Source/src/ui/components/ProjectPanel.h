#pragma once

#include "Panel.h"

namespace BoxerEngine
{
    class ProjectPanel final : public Panel
    {
    public:
        ProjectPanel();
        ~ProjectPanel() override = default;

        void Update() override;
    };
}
