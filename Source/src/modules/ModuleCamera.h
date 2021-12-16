#pragma once

#include "Module.h"
#include "Globals.h"
#include "Math/float4x4.h"
#include "MathGeoLib.h"

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
	~ModuleCamera();

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	bool CleanUp() override;

	[[nodiscard]] float4x4 GetViewMatrix() const;
	[[nodiscard]] float4x4 GetProjectionMatrix() const;
	[[nodiscard]] const float3& GetPosition() const;
	[[nodiscard]] float GetAspectRatio() const;
	[[nodiscard]] float GetHorizontalFovDegrees() const;

	[[nodiscard]] float GetMoveSpeed() const { return Speed; };
	[[nodiscard]] float GetZoomPosSpeed() const { return ZoomPosSpeed; };
	[[nodiscard]] float GetRotationSpeed() const { return RotationSpeed; };
	[[nodiscard]] float GetOrbitSpeed() const { return OrbitSpeed; };

	void SetPosition(const float3& position);
	void Rotate(float pitch, float yaw, float roll);
	void SetAspectRatio(unsigned int width, unsigned int height);
	void SetHorizontalFovInDegrees(float fovDegree);
	void SetPlaneDistances(const float nearDist, const float farDist);
	void SetDefaultValues();

	void SetMoveSpeed(const float speed) { Speed = speed; };
	void SetZoomPosSpeed(const float speed) { ZoomPosSpeed = speed; };
	void SetRotationSpeed(const float speed) { RotationSpeed = speed; };
	void SetOrbitSpeed(const float speed) { OrbitSpeed = speed; };

	void Look(const float3& position);
	void LookModule();
	void ZoomInPosition();
	void ZoomOutPosition();

private:
	Frustum CameraFrustum;
	// Projection
	float AspectRatio;
	float HorizontalFovDegree;
	float NearDistance;
	float FarDistance;
	// Speed
	float Speed;
	float RotationSpeed;
	float ZoomPosSpeed;
	float ZoomFovSpeed;
	float OrbitSpeed;

	float OrbitAngle;
	// Rotation (WIP)
	float Roll;
	float Pitch;
	float Yaw;
	void SetRotationMatrix();
	float4x4 RotationMatrix;
	float4x4 TranslationMatrix;

	float3 LookPosition;
	float3 Position;

	void CameraInputs();
	void TranslationInputs();
	void AspectInputs();
	void RotationInputs();
	void OrbitModule();

	float GetSpeed(MoveType type = MoveType::TRANSLATION) const;
	void ZoomOutFOV();
	void ZoomInFOV();
};

