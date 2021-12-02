#include "ModuleCamera.h"

#include "Math/float3x3.h"

constexpr auto DEGTORAD = 0.0174532925199432957f; // PI/180

ModuleCamera::ModuleCamera() = default;

ModuleCamera::~ModuleCamera() = default;

bool ModuleCamera::Init()
{
    frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
    frustum.SetViewPlaneDistances(0.1f, 100.0f);
    frustum.SetHorizontalFovAndAspectRatio(DEGTORAD * 90.0f, static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT));
    frustum.SetPos(float3(1.0f, 2.5f, -5.0f));
    frustum.SetFront(float3::unitZ);
    frustum.SetUp(float3::unitY);
    //
    LookAt(float3(0.0f));

    model = float4x4::identity;
    view = frustum.ViewMatrix();
    projection = frustum.ProjectionMatrix();

    return true;
}

update_status ModuleCamera::Update()
{
    return UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp()
{
    return true;
}

void ModuleCamera::LookAt(const float3& position)
{
    const float3 direction = position - frustum.Pos();
    const float3x3 look = float3x3::LookAt(frustum.Front(), direction.Normalized(), frustum.Up(), float3::unitY);
    frustum.SetFront(look.MulDir(frustum.Front()).Normalized());
    frustum.SetUp(look.MulDir(frustum.Up()).Normalized());

}
