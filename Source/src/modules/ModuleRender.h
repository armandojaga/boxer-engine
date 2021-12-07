#pragma once

#include "Module.h"
#include "Globals.h"
#include "GL/glew.h"
#include "core/rendering/FrameBuffer.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRender : public Module
{
public:
    ModuleRender() = default;
    ~ModuleRender() override = default;

    bool Init() override;
    update_status PreUpdate() override;
    update_status Update() override;
    update_status PostUpdate() override;
    bool CleanUp() override;
    void Resize(int width, int height);
    void* GetContext() const;

    [[nodiscard]] BoxerEngine::FrameBuffer& GetFrameBuffer() const
    {
        return *frame_buffer;
    }

private:
    void* context{};
    int width{}, height{};
    std::unique_ptr<BoxerEngine::FrameBuffer> frame_buffer;
};
