#pragma once

#include "Module.h"
#include "ui/components/AboutPanel.h"
#include "ui/components/ConfigurationPanel.h"
#include "ui/components/ConsolePanel.h"
#include "ui/components/HardwarePanel.h"
#include "ui/components/HierarchyPanel.h"
#include "ui/components/InspectorPanel.h"
#include "ui/components/ScenePanel.h"
#include "ui/components/StatisticsPanel.h"

class ModuleEditor : public Module
{
public:
    ModuleEditor();
    ~ModuleEditor() override;

    bool Init() override;
    update_status PreUpdate(float delta) override;
    update_status Update(float delta) override;
    update_status PostUpdate(float delta) override;
    bool CleanUp() override;

    static void SetActiveEntity(BoxerEngine::Entity* const entity);

private:
    void CreateDockerspace() const;
    void CreateMenu() const;
    void ShowCameraSettings() const;

private:
    std::shared_ptr<BoxerEngine::ScenePanel> scenePanel = nullptr;
    std::shared_ptr<BoxerEngine::HierarchyPanel> hierarchyPanel = nullptr;
    std::shared_ptr<BoxerEngine::InspectorPanel> inspectorPanel = nullptr;
    std::shared_ptr<BoxerEngine::ConfigurationPanel> configurationPanel = nullptr;
    std::shared_ptr<BoxerEngine::ConsolePanel> consolePanel = nullptr;
    std::shared_ptr<BoxerEngine::StatisticsPanel> statisticsPanel = nullptr;
    std::shared_ptr<BoxerEngine::HardwarePanel> hardwarePanel = nullptr;
    std::shared_ptr<BoxerEngine::AboutPanel> aboutPanel = nullptr;

    mutable bool display_camera_settings = false;
    mutable bool should_exit = false;

    std::vector<std::shared_ptr<BoxerEngine::Panel>> panels{};
};
