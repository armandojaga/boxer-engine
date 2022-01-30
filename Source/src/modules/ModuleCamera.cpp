#include "ModuleCamera.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "core/rendering/Model.h"

#include "MathGeoLib.h"

static const float DEGTORAD = pi / 180.0f;
static const float EPSILON = 1e-5f;

ModuleCamera::ModuleCamera()
    : aspect_ratio(0.0f)
      , horizontal_fov_degree(0.0f)
      , near_distance(0.0f)
      , far_distance(0.0f)
      , move_speed(15.0f)
      , rotation_speed(15.0f)
      , zoom_pos_speed(50.0f)
      , zoom_fov_speed(0.05f)
      , orbit_speed(25.0f)
      , orbit_angle(0.0f)
      , roll(0.0f)
      , pitch(0.0f)
      , yaw(0.0f)
      , look_position(float3::zero)
      , position(float3::zero)
{
}

ModuleCamera::~ModuleCamera() = default;

bool ModuleCamera::Init()
{
    camera_preferences = static_cast<BoxerEngine::CameraPreferences*>(App->preferences->GetPreferenceDataByType(BoxerEngine::Preferences::Type::CAMERA));
    near_distance = camera_preferences->GetNearDistance();
    far_distance = camera_preferences->GetFarDistance();
    move_speed = camera_preferences->GetMoveSpeed();
    rotation_speed = camera_preferences->GetRotationSpeed();
    zoom_pos_speed = camera_preferences->GetZoomSpeed();
    orbit_speed = camera_preferences->GetOrbitSpeed();
    horizontal_fov_degree = camera_preferences->GetFOV();

    camera_frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
    SetAspectRatio(SCREEN_WIDTH, SCREEN_HEIGHT);
    SetHorizontalFovInDegrees(horizontal_fov_degree);
    SetPlaneDistances(near_distance, far_distance);
    SetPosition(float3(8.0f, 8.0f, 8.0f));
    const float3x3 rotation = float3x3::identity;
    camera_frustum.SetFront(rotation.WorldZ());
    camera_frustum.SetUp(rotation.WorldY());
    Look(float3(0.0f, 0.0f, 0.0f));
    return true;
}

update_status ModuleCamera::PreUpdate(float delta)
{
    return update_status::UPDATE_CONTINUE;
}

update_status ModuleCamera::Update(float delta)
{
    CameraInputs();
    return update_status::UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp()
{
    camera_preferences->SetFarDistance(far_distance);
    camera_preferences->SetMoveSpeed(move_speed);
    camera_preferences->SetNearDistance(near_distance);
    camera_preferences->SetOrbitSpeed(orbit_speed);
    camera_preferences->SetRotationSpeed(rotation_speed);
    camera_preferences->SetZoomSpeed(zoom_pos_speed);
    camera_preferences->SetFOV(horizontal_fov_degree);
    return true;
}

float4x4 ModuleCamera::GetViewMatrix() const
{
    // TODO: Return view matrix from roll, pitch & yaw values
    auto rotation = Quat();
    rotation.RotateX(pitch);
    rotation.RotateY(yaw);
    rotation.RotateZ(roll);
    rotation.Inverse();
    return float4x4(camera_frustum.ViewMatrix());
}

float4x4 ModuleCamera::GetProjectionMatrix() const
{
    return camera_frustum.ProjectionMatrix();
}

void ModuleCamera::SetPosition(const float3& new_pos)
{
    camera_frustum.SetPos(position = new_pos);
}

const float3& ModuleCamera::GetPosition() const
{
    return position;
}

// Deprecate below method
void ModuleCamera::Rotate(float pitch = 0.0f, float yaw = 0.0f, float roll = 0.0f)
{
    if (yaw > EPSILON || yaw < EPSILON)
    {
        // Rotate in Y absolut axis
        const Quat rot = Quat::RotateY(yaw);
        camera_frustum.SetFront(rot.Mul(camera_frustum.Front()).Normalized());
        camera_frustum.SetUp(rot.Mul(camera_frustum.Up()).Normalized());
    }

    if (pitch > EPSILON || pitch < EPSILON)
    {
        // Rotate in X local axis
        const Quat rot = Quat::RotateAxisAngle(camera_frustum.WorldRight(), pitch);
        camera_frustum.SetUp(rot.Mul(camera_frustum.Up()).Normalized());
        camera_frustum.SetFront(rot.Mul(camera_frustum.Front()).Normalized());
    }
}

void ModuleCamera::SetAspectRatio(unsigned int width, unsigned int height)
{
    aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
    camera_frustum.SetHorizontalFovAndAspectRatio(horizontal_fov_degree * DEGTORAD, aspect_ratio);
}

float ModuleCamera::GetAspectRatio() const
{
    return camera_frustum.AspectRatio();
}

void ModuleCamera::SetHorizontalFovInDegrees(float fovDegree)
{
    horizontal_fov_degree = fovDegree;
    camera_frustum.SetHorizontalFovAndAspectRatio(horizontal_fov_degree * DEGTORAD, aspect_ratio);
}

float ModuleCamera::GetHorizontalFovDegrees() const
{
    return horizontal_fov_degree;
}

void ModuleCamera::Look(const float3& position)
{
    const float3 direction = look_position - camera_frustum.Pos();
    const float3x3 lookDir = float3x3::LookAt(camera_frustum.Front(), direction.Normalized(), camera_frustum.Up(), float3::unitY);

    camera_frustum.SetFront(lookDir.MulDir(camera_frustum.Front()).Normalized());
    camera_frustum.SetUp(lookDir.MulDir(camera_frustum.Up()).Normalized());
}

void ModuleCamera::LookModule()
{
    // const float3 moduleSizes = App->renderer->GetModel()->GetModelSizeFactor();
    // const float iSum = 1 / (moduleSizes.x + moduleSizes.y + moduleSizes.z);
    // const float posX = (moduleSizes.y + moduleSizes.z) * moduleSizes.x * iSum;
    // const float posY = (moduleSizes.x + moduleSizes.z) * moduleSizes.y * iSum;
    // const float posZ = (moduleSizes.x + moduleSizes.y) * moduleSizes.z * iSum;
    // const float3 position = float3(8.0f + posX, 8.0f + posY, 8.0f + posZ);
    // SetPosition(position);
    Look(float3(0.0f));
}

void ModuleCamera::SetRotationMatrix()
{
    //WIP
}

void ModuleCamera::CameraInputs()
{
    TranslationInputs();
    RotationInputs();
    AspectInputs();
}

inline void ModuleCamera::TranslationInputs()
{
    if (App->input->IsKeyPressed(SDL_SCANCODE_W))
    {
        position += camera_frustum.Front() * GetSpeed(MoveType::TRANSLATION);
    }

    if (App->input->IsKeyPressed(SDL_SCANCODE_S))
    {
        position -= camera_frustum.Front() * GetSpeed(MoveType::TRANSLATION);
    }

    if (App->input->IsKeyPressed(SDL_SCANCODE_D))
    {
        position += camera_frustum.WorldRight() * GetSpeed(MoveType::TRANSLATION);
    }

    if (App->input->IsKeyPressed(SDL_SCANCODE_A))
    {
        position -= camera_frustum.WorldRight() * GetSpeed(MoveType::TRANSLATION);
    }

    if (App->input->GetMouseWheel().y > 0)
    {
        ZoomInPosition();
    }
    else if (App->input->GetMouseWheel().y < 0)
    {
        ZoomOutPosition();
    }

    SetPosition(position);
}

inline void ModuleCamera::AspectInputs()
{
    if (App->input->IsKeyPressed(SDL_SCANCODE_Q))
    {
        ZoomOutFOV();
    }

    if (App->input->IsKeyPressed(SDL_SCANCODE_E))
    {
        ZoomInFOV();
    }

    SetHorizontalFovInDegrees(horizontal_fov_degree);
}

inline void ModuleCamera::RotationInputs()
{
    // Keyboard
    if (App->input->IsKeyPressed(SDL_SCANCODE_UP))
    {
        pitch += GetSpeed(MoveType::ROTATION);
        // Deprecate below
        Rotate(GetSpeed(MoveType::ROTATION), 0.0f);
    }

    if (App->input->IsKeyPressed(SDL_SCANCODE_DOWN))
    {
        pitch -= GetSpeed(MoveType::ROTATION);
        // Deprecate below
        Rotate(-GetSpeed(MoveType::ROTATION), 0.0f);
    }

    if (App->input->IsKeyPressed(SDL_SCANCODE_LEFT))
    {
        yaw += GetSpeed(MoveType::ROTATION);
        // Deprecate below
        Rotate(0.0f, GetSpeed(MoveType::ROTATION));
    }

    if (App->input->IsKeyPressed(SDL_SCANCODE_RIGHT))
    {
        yaw -= GetSpeed(MoveType::ROTATION);
        // Deprecate below
        Rotate(0.0f, -GetSpeed(MoveType::ROTATION));
    }

    if (App->input->GetKey(SDL_SCANCODE_F) == KeyState::KEY_DOWN)
    {
        LookModule();
    }

    // Mouse
    if (App->input->IsMouseButtonPressed(SDL_BUTTON_RIGHT))
    {
        yaw += App->input->GetMouseMotion().x * GetSpeed(MoveType::ROTATION);
        pitch += App->input->GetMouseMotion().y * GetSpeed(MoveType::ROTATION);
        // Deprecate below
        const float mouseMotionX = App->input->GetMouseMotion().x;
        const float mouseMotionY = App->input->GetMouseMotion().y;
        Rotate(-0.01f * mouseMotionY, -0.01f * mouseMotionX);
    }

    // Orbit
    if (App->input->IsModKeyPressed(KMOD_ALT) && App->input->IsMouseButtonPressed(SDL_BUTTON_LEFT))
    {
        OrbitModule();
    }
}

void ModuleCamera::OrbitModule()
{
    const BoxerEngine::Model* model = App->renderer->GetModel();
    if (model == nullptr)
    {
        return;
    }
    const float3 moduleOrigin = float3(0.0f);//model->GetOrigin(); TODO: take selected object model transform

    // Radius is the distance to the module in xz plane
    auto distanceXZ = float2(position.x - moduleOrigin.x, position.z - moduleOrigin.z);
    const float radius = sqrt((distanceXZ.x * distanceXZ.x) + (distanceXZ.y * distanceXZ.y));

    orbit_angle += GetSpeed(MoveType::ORBIT);
    const auto pos = float3(sin(orbit_angle * DEGTORAD) * radius,
                            position.y,
                            cos(orbit_angle * DEGTORAD) * radius);
    SetPosition(pos);
    Look(moduleOrigin);
}

void ModuleCamera::ZoomInPosition()
{
    position += camera_frustum.Front() * GetSpeed(MoveType::ZOOM_POS);
}

void ModuleCamera::ZoomOutPosition()
{
    position -= camera_frustum.Front() * GetSpeed(MoveType::ZOOM_POS);
}

inline void ModuleCamera::ZoomOutFOV()
{
    if (horizontal_fov_degree >= 120.0f)
    {
        return;
    }
    horizontal_fov_degree += horizontal_fov_degree * GetSpeed(MoveType::ZOOM_FOV);
}

inline void ModuleCamera::ZoomInFOV()
{
    if (horizontal_fov_degree <= EPSILON)
    {
        return;
    }
    horizontal_fov_degree -= horizontal_fov_degree * GetSpeed(MoveType::ZOOM_FOV);
}

inline float ModuleCamera::GetSpeed(MoveType type) const
{
    float speed;
    float multiplier = 1.0f;
    switch (type)
    {
    case MoveType::TRANSLATION:
        speed = move_speed;
        break;
    case MoveType::ROTATION:
        speed = rotation_speed;
        break;
    case MoveType::ZOOM_POS:
        speed = zoom_pos_speed;
        break;
    case MoveType::ZOOM_FOV:
        speed = zoom_fov_speed;
        break;
    case MoveType::ORBIT:
        speed = orbit_speed;
        break;
    default:
        speed = move_speed;
        break;
    }
    if (App->input->IsModKeyPressed(KMOD_SHIFT))
    {
        multiplier = 2.0f;
    }
    const auto delta = App->GetDelta();
    return speed * delta * multiplier;
}

void ModuleCamera::SetPlaneDistances(const float nearDist, const float farDist)
{
    camera_frustum.SetViewPlaneDistances(near_distance = nearDist, far_distance = farDist);
}

void ModuleCamera::SetDefaultValues()
{
    Init();
}
