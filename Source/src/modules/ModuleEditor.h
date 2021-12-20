#pragma once

#include "Module.h"
#include "ui/components/ConsolePanel.h"

class ModuleEditor : public Module
{
private:
    BoxerEngine::ConsolePanel* console;
    bool display_about = false;
    bool display_console = true;
    bool display_stats = true;
    bool display_config = true;
    bool display_hardware = true;
    bool display_camera_settings = false;
    bool should_exit = false;
    mutable std::string license_content;

public:
    ModuleEditor();
    ~ModuleEditor() override;

    bool Init() override;
    update_status PreUpdate(float delta) override;
    update_status Update(float delta) override;
    update_status PostUpdate(float delta) override;
    bool CleanUp() override;

private:
    void CreateMenu();
    // TODO: A pointer to bool is more expensive than the bool itself
    void ShowConsole(bool*) const;
    void ShowStats(bool*) const;
    void ShowConfig(bool*) const;
    void ShowHardware(bool*) const;
    void ShowAbout(bool*) const;
    void ShowCameraSettings(bool open) const;
    void CreateScene();
};
