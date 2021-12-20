#pragma once

#include "Module.h"

#include "Math/float4x4.h"

class DDRenderInterfaceCoreGL;
class Camera;

class ModuleDebugDraw : public Module
{
public:
    unsigned int textureId;
    ModuleDebugDraw();
    ~ModuleDebugDraw() override;

    bool Init() override;
    update_status Update(float delta) override;
    bool CleanUp() override;

    void Draw(const float4x4& view, const float4x4& proj, unsigned width, unsigned height);
private:
    static DDRenderInterfaceCoreGL* implementation;
};
