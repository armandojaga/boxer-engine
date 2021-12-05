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
    bool should_exit = false;
    mutable std::string license_content;

    uint32_t mFBO = 0;
    uint32_t mTexId = 0;
    uint32_t mDepthId = 0;

public:
    ModuleEditor();
    ~ModuleEditor() override;

    bool Init() override;
    update_status PreUpdate() override;
    update_status Update() override;
    update_status PostUpdate() override;
    bool CleanUp() override;

private:
    void CreateMenu();
    void ShowConsole(bool*) const;
    void ShowStats(bool*) const;
    void ShowConfig(bool*) const;
    void ShowHardware(bool*) const;
    void ShowAbout(bool*) const;
};
