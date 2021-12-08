#pragma once

#include "Module.h"
#include <GL/glew.h>
#include <Geometry/Frustum.h>

class ModuleCamera : public Module
{
private:
    Frustum frustum;
    float4x4 model;
    float4x4 view;
    float4x4 projection;

    //speeds
    float move_speed = 0.5f;
    float rotation_speed = 0.005f;
    float orbit_speed = 0.02f;


public:
    ModuleCamera();
    ~ModuleCamera() override;

    bool Init() override;
    
    update_status PreUpdate() override;
    update_status Update() override;
    bool CleanUp() override;
    void LookAt(const float3& position);
    void Resize(int width, int height);

    [[nodiscard]] const float4x4& GetModelMatrix() const
    {
        return model;
    }

    [[nodiscard]] const float4x4& GetViewMatrix() const
    {
        return view;
    }

    [[nodiscard]] const float4x4& GetProjectionMatrix() const
    {
        return projection;
    }



private:
    void SetAspectRatio(float ar);
    void HandleMovement();
};
