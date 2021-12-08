#pragma once
#include "Module.h"
#include "Globals.h"
#include "Math/float2.h"

constexpr int NUM_MOUSE_BUTTONS = 5;

enum class KeyState
{
    KEY_IDLE = 0,
    KEY_DOWN,
    KEY_REPEAT,
    KEY_UP
};

class ModuleInput : public Module
{
public:
    ModuleInput();
    ~ModuleInput() override;

    bool Init() override;
    update_status PreUpdate() override;
    bool CleanUp() override;

    [[nodiscard]] KeyState GetKey(int id) const
    {
        return keyboard[id];
    }

    [[nodiscard]] KeyState GetMouseButtonDown(int id) const
    {
        return mouse_buttons[id - 1];
    }

    [[nodiscard]] const float2& GetMousePosition() const
    {
        return mouse_position;
    }

    [[nodiscard]] const float2& GetMouseMotion() const
    {
        return mouse_motion;
    }

    [[nodiscard]] const float2& GetMouseWheel() const
    {
        return mouse_wheel;
    }

private:
    KeyState* keyboard = nullptr;
    KeyState mouse_buttons[NUM_MOUSE_BUTTONS]{};
    float2 mouse_position = float2::zero;
    float2 mouse_motion = float2::zero;
    float2 mouse_wheel = float2::zero;
};
