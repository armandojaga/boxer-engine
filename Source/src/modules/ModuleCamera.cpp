#include "ModuleCamera.h"

#include "Application.h"
#include "ModuleInput.h"
#include "SDL_mouse.h"
#include "Math/float3x3.h"
#include "Math/Quat.h"

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
    
    LookAt(float3(0.0f));

    model = float4x4::identity;
    view = frustum.ViewMatrix();
    projection = frustum.ProjectionMatrix();

    return true;
}

update_status ModuleCamera::PreUpdate()
{

    HandleMovement();

    projection = frustum.ProjectionMatrix();
    return update_status::UPDATE_CONTINUE;
}

update_status ModuleCamera::Update()
{
    return update_status::UPDATE_CONTINUE;
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

void ModuleCamera::SetAspectRatio(float ar)
{
    frustum.SetHorizontalFovAndAspectRatio(frustum.HorizontalFov(), ar);
}

void ModuleCamera::Resize(int width, int height)
{
    SetAspectRatio(static_cast<float>(width) / static_cast<float>(height));
}

void ModuleCamera::HandleMovement()
{
    auto dt = App->GetDelta();
    auto btn = App->input->GetMouseButtonDown(SDL_BUTTON_LEFT);
    if (btn == KeyState::KEY_DOWN || btn == KeyState::KEY_REPEAT) {
        auto motion = App->input->GetMouseMotion();
        auto stepx = motion.x * rotation_speed * dt;
        auto stepy = motion.y * rotation_speed * dt;


        frustum.Transform(Quat::RotateY(stepy));
        frustum.Transform(Quat::RotateAxisAngle(frustum.WorldRight(), stepx));
        //TODO FIX this
    }
}