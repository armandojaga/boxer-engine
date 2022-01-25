#pragma once
#include "Panel.h"

namespace BoxerEngine
{
    class StatisticsPanel final : public Panel
    {
    public:
        StatisticsPanel();
        ~StatisticsPanel() override = default;

        void Update() override;
    };
}
