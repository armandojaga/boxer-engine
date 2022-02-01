#pragma once

#include "Panel.h"
#include <filesystem>

namespace BoxerEngine
{
    class ProjectPanel final : public Panel
    {
    public:
        ProjectPanel();
        ~ProjectPanel() override = default;

        void Update() override;
    private:
        void ImportAsset(const std::string& path);
        std::filesystem::path current_directory = "./assets";
    };
}
