#pragma once

#include "Module.h"
#include "ui/components/ConsolePanel.h"

class ModuleEditor : public Module
{
private:
    BoxerEngine::ConsolePanel* console;
    mutable bool display_about = false;
    mutable bool display_console = true;
    mutable bool display_stats = true;
    mutable bool display_config = true;
    mutable bool display_hardware = true;
    mutable bool display_camera_settings = false;
    mutable bool should_exit = false;
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
    void CreateDockerspace() const;
    void CreateMenu() const ;
    void ShowConsole() const;
    void ShowStats() const;
    void ShowConfig() const;
    void ShowHardware() const;
    void ShowAbout() const;
    void ShowCameraSettings() const;
    void CreateScene() const;
};
