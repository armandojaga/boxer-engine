#pragma once
#include "Panel.h"

namespace BoxerEngine
{
    class ConfigurationPanel final : public Panel
    {
    public:
        ConfigurationPanel();
        ~ConfigurationPanel() override = default;

        void Update() override;
    };
}
