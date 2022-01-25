#pragma once

#include "Module.h"
#include "Globals.h"
#include "Math/float4x4.h"
#include "MathGeoLib.h"
#include "core/preferences/editor/CameraPreferences.h"

enum class MoveType
{
    TRANSLATION = 0,
    ROTATION,
    ZOOM_POS,
    ZOOM_FOV,
    ORBIT
};

class ModuleCamera : public Module
{
public:
    ModuleCamera();
    ~ModuleCamera() override;

    bool Init() override;
    update_status PreUpdate(float delta) override;
    update_status Update(float delta) override;
    bool CleanUp() override;

    [[nodiscard]] float4x4 GetViewMatrix() const;
    [[nodiscard]] float4x4 GetProjectionMatrix() const;
    [[nodiscard]] const float3& GetPosition() const;
    [[nodiscard]] float GetAspectRatio() const;
    [[nodiscard]] float GetHorizontalFovDegrees() const;

    [[nodiscard]] float GetMoveSpeed() const { return move_speed; };
    [[nodiscard]] float GetZoomPosSpeed() const { return zoom_pos_speed; };
    [[nodiscard]] float GetRotationSpeed() const { return rotation_speed; };
    [[nodiscard]] float GetOrbitSpeed() const { return orbit_speed; };

    void SetPosition(const float3& position);
    void Rotate(float pitch, float yaw, float roll);
    void SetAspectRatio(unsigned int width, unsigned int height);
    void SetHorizontalFovInDegrees(float fovDegree);
    void SetPlaneDistances(float nearDist, float farDist);
    void SetDefaultValues();

    void SetMoveSpeed(const float speed) { move_speed = speed; };
    void SetZoomPosSpeed(const float speed) { zoom_pos_speed = speed; };
    void SetRotationSpeed(const float speed) { rotation_speed = speed; };
    void SetOrbitSpeed(const float speed) { orbit_speed = speed; };

    void Look(const float3& position);
    void LookModule();
    void ZoomInPosition();
    void ZoomOutPosition();

private:
    Frustum camera_frustum;
    BoxerEngine::CameraPreferences* camera_preferences = nullptr;
    // Projection
    float aspect_ratio;
    float horizontal_fov_degree;
    float near_distance;
    float far_distance;

    // Speed
    float move_speed;
    float rotation_speed;
    float zoom_pos_speed;
    float zoom_fov_speed;
    float orbit_speed;

    float orbit_angle;

    // Rotation (WIP)
    float roll;
    float pitch;
    float yaw;
    void SetRotationMatrix();
    float4x4 rotation_matrix;
    float4x4 translation_matrix;

    float3 look_position;
    float3 position;

    void CameraInputs();
    void TranslationInputs();
    void AspectInputs();
    void RotationInputs();
    void OrbitModule();

    float GetSpeed(MoveType type = MoveType::TRANSLATION) const;
    void ZoomOutFOV();
    void ZoomInFOV();
};
