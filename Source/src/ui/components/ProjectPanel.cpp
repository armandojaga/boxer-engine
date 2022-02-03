#include "core/bepch.h"
#include "ProjectPanel.h"

#include "modules/ModuleResources.h"

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
        auto relative_path = relative(path, assets_path);
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
            auto selection = ImGui::Selectable(filename.c_str(), ImGuiSelectableFlags_AllowDoubleClick);
            if (ImGui::IsMouseDoubleClicked(selection) && ImGui::IsItemHovered())
            {
                filename.insert(0, "\\");
                filename.insert(0, current_directory.string().c_str());
                ImportAsset(filename);
            }
        }
    }

    ImGui::End();
}

void BoxerEngine::ProjectPanel::ImportAsset(const std::string& path)
{
    Event assetChanged(Event::Type::ASSETS_CHANGED);
    assetChanged.SetEventData<AssetsAddedEventPayload>(path, App->resources->GetType(path));
    EventManager::GetInstance().Publish(assetChanged);
}
