#include "core/bepch.h"
#include "ProjectPanel.h"

BoxerEngine::ProjectPanel::ProjectPanel() : Panel("Project", true)
{
}

void BoxerEngine::ProjectPanel::Update()
{
    ImGui::SetNextWindowSize(ImVec2(1100, 170), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(StringUtils::Concat(ICON_MD_FOLDER_SPECIAL, GetTitle()).c_str(), &visible))
    {
        ImGui::End();
        return;
    }
    std::filesystem::path assets_path("./assets");

    if (current_directory != assets_path)
    {
        if (ImGui::Button(ICON_MD_SUBDIRECTORY_ARROW_LEFT))
        {
            current_directory = current_directory.parent_path();
        }
    }

    for (auto& directory_entry : std::filesystem::directory_iterator(current_directory))
    {
        const auto& path = directory_entry.path();
        auto relative_path = std::filesystem::relative(path, assets_path);
        std::string filename = relative_path.filename().string();

        if (directory_entry.is_directory())
        {
            if (ImGui::Button(filename.c_str()))
            {
                current_directory /= path.filename();
            }
        }
        else
        {
            if (ImGui::Button(filename.c_str()))
            {
            }
        }
    }

    ImGui::End();
}
