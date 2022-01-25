#pragma once
#include "Panel.h"

namespace BoxerEngine
{
    class AboutPanel final : public Panel
    {
    public:
        AboutPanel();
        ~AboutPanel() override = default;

        void Update() override;

    private:
        mutable std::string license_content;
    };
}
