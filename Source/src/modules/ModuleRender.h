#pragma once

#include "Module.h"
#include "Globals.h"
#include "GL/glew.h"
#include "core/rendering/FrameBuffer.h"
#include "core/rendering/Model_A.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRender : public Module
{
public:
    ModuleRender() = default;
    ~ModuleRender() override;

    bool Init() override;
    bool Start() override;
    update_status PreUpdate(float delta) override;
    update_status Update(float delta) override;
    update_status PostUpdate(float delta) override;
    bool CleanUp() override;
    void Resize(int width, int height);
    [[nodiscard]] void* GetContext() const;

    [[nodiscard]] const Model_A* GetModel() const
    {
        return model;
    }

    [[nodiscard]] BoxerEngine::FrameBuffer* GetFrameBuffer() const
    {
        return frame_buffer;
    }

    void LoadModel(const char* filPath)
    {
        delete model;
        model = new Model_A();
        model->Load(filPath);
    }

private:
    void* context{};
    int width{}, height{};
    BoxerEngine::FrameBuffer* frame_buffer;
    Model_A* model = nullptr;

};
