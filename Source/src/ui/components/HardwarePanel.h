#pragma once
#include "Panel.h"

namespace BoxerEngine
{
    class HardwarePanel final : public Panel
    {
    public:
        HardwarePanel();
        ~HardwarePanel() override = default;

        void Update() override;
    };
}
