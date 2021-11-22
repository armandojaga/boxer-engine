#pragma once

#include "Console.h"
#include "Module.h"

class ModuleEditor : public Module
{
private:
    BoxerEngine::Console* console;
    bool display_console = false;
    bool display_stats = false;
    bool should_exit = false;

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
};
