#include "ModuleCamera.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "core/rendering/Model.h"

#include "GL/glew.h"
#include "MathGeoLib.h"

static const float DEGTORAD = math::pi / 180.0;
static const float EPSILON = 1e-5;

ModuleCamera::ModuleCamera()
    : AspectRatio(0.0f)
    , HorizontalFovDegree(0.0f)
    , NearDistance(0.0f)
    , FarDistance(0.0f)
    , Speed(0.05f)
    , RotationSpeed(0.05f)
    , ZoomPosSpeed(0.1f)
    , ZoomFovSpeed(0.0005f)
    , OrbitSpeed(0.1f)
    , OrbitAngle(0.0f)
    , Roll(0.0f)
    , Pitch(0.0f)
    , Yaw(0.0f)
    , LookPosition(float3::zero)
    , Position(float3::zero)
{
}

ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Init()
{
    CameraFrustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
    SetAspectRatio(static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT));
    SetHorizontalFovInDegrees(90.0f);
    SetPlaneDistances(0.1f, 200.0f);
    SetPosition(float3(8.0f, 8.0f, 8.0f));
    float3x3 rotation = float3x3::identity;
    CameraFrustum.SetFront(rotation.WorldZ());
    CameraFrustum.SetUp(rotation.WorldY());
    Look(float3(0.0f, 0.0f, 0.0f));
    return true;
}

update_status ModuleCamera::PreUpdate()
{
    return update_status::UPDATE_CONTINUE;
}

update_status ModuleCamera::Update()
{
    CameraInputs();
    return update_status::UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp()
{
    return true;
}

float4x4 ModuleCamera::GetViewMatrix()
{
    // TODO: Return view matrix from roll, pitch & yaw values
    Quat rotation = Quat();
    rotation.RotateX(Pitch);
    rotation.RotateY(Yaw);
    rotation.RotateZ(Roll);
    rotation.Inverse();
    return float4x4(CameraFrustum.ViewMatrix());
    //return 
}

float4x4 ModuleCamera::GetProjectionMatrix()
{
    return CameraFrustum.ProjectionMatrix();
}

void ModuleCamera::SetPosition(const float3& position)
{
    CameraFrustum.SetPos(Position = position);
}

const float3& ModuleCamera::GetPosition() const
{
    return Position;
}

// Deprecate below method
void ModuleCamera::Rotate(float pitch = 0.0f, float yaw = 0.0f, float roll = 0.0f)
{
    if (yaw > EPSILON || yaw < EPSILON)
    {
        // Rotate in Y absolut axis
        Quat rot = Quat::RotateY(yaw);
        CameraFrustum.SetFront(rot.Mul(CameraFrustum.Front()).Normalized());
        CameraFrustum.SetUp(rot.Mul(CameraFrustum.Up()).Normalized());
    }

    if (pitch > EPSILON || pitch < EPSILON)
    {
        // Rotate in X local axis
        Quat rot = Quat::RotateAxisAngle(CameraFrustum.WorldRight(), pitch);
        CameraFrustum.SetUp(rot.Mul(CameraFrustum.Up()).Normalized());
        CameraFrustum.SetFront(rot.Mul(CameraFrustum.Front()).Normalized());
    }
}

void ModuleCamera::SetAspectRatio(unsigned int width, unsigned int height)
{
    AspectRatio = (float)width / (float)height;
    CameraFrustum.SetHorizontalFovAndAspectRatio(HorizontalFovDegree * DEGTORAD, AspectRatio);
}

float ModuleCamera::GetAspectRatio() const
{
    return CameraFrustum.AspectRatio();
}

void ModuleCamera::SetHorizontalFovInDegrees(float fovDegree)
{
    HorizontalFovDegree = fovDegree;
    CameraFrustum.SetHorizontalFovAndAspectRatio(HorizontalFovDegree * DEGTORAD, AspectRatio);
}

float ModuleCamera::GetHorizontalFovDegrees() const
{
    return HorizontalFovDegree;
}

void ModuleCamera::Look(const float3& position)
{
    float3 direction = LookPosition - CameraFrustum.Pos();
    float3x3 lookDir = float3x3::LookAt(CameraFrustum.Front(), direction.Normalized(), CameraFrustum.Up(), float3::unitY);

    CameraFrustum.SetFront(lookDir.MulDir(CameraFrustum.Front()).Normalized());
    CameraFrustum.SetUp(lookDir.MulDir(CameraFrustum.Up()).Normalized());
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
    if (App->input->GetKey(SDL_SCANCODE_W) == KeyState::KEY_DOWN)
    {
        Position += CameraFrustum.Front() * GetSpeed(MoveType::TRANSLATION);
    }

    if (App->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_DOWN)
    {
        Position -= CameraFrustum.Front() * GetSpeed(MoveType::TRANSLATION);
    }

    if (App->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_DOWN)
    {
        Position += CameraFrustum.WorldRight() * GetSpeed(MoveType::TRANSLATION);
    }

    if (App->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_DOWN)
    {
        Position -= CameraFrustum.WorldRight() * GetSpeed(MoveType::TRANSLATION);
    }

    SetPosition(Position);
}

inline void ModuleCamera::AspectInputs()
{
    if (App->input->GetKey(SDL_SCANCODE_Q) == KeyState::KEY_DOWN)
    {
        ZoomOutFOV();
    }

    if (App->input->GetKey(SDL_SCANCODE_E) == KeyState::KEY_DOWN)
    {
        ZoomInFOV();
    }
    SetHorizontalFovInDegrees(HorizontalFovDegree);
}

inline void ModuleCamera::RotationInputs()
{
    // Keyboard
    if (App->input->GetKey(SDL_SCANCODE_UP) == KeyState::KEY_DOWN)
    {
        Pitch += GetSpeed(MoveType::ROTATION);
        // Deprecate below
        Rotate(GetSpeed(MoveType::ROTATION), 0.0f);
    }
    if (App->input->GetKey(SDL_SCANCODE_DOWN) == KeyState::KEY_DOWN)
    {
        Pitch -= GetSpeed(MoveType::ROTATION);
        // Deprecate below
        Rotate(-GetSpeed(MoveType::ROTATION), 0.0f);
    }
    if (App->input->GetKey(SDL_SCANCODE_LEFT) == KeyState::KEY_DOWN)
    {
        Yaw += GetSpeed(MoveType::ROTATION);
        // Deprecate below
        Rotate(0.0f, GetSpeed(MoveType::ROTATION));
    }
    if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KeyState::KEY_DOWN)
    {
        Yaw -= GetSpeed(MoveType::ROTATION);
        // Deprecate below
        Rotate(0.0f, -GetSpeed(MoveType::ROTATION));
    }

    if (App->input->GetKey(SDL_SCANCODE_F) == KeyState::KEY_DOWN)
    {
        LookModule();
    }

    // Mouse
    if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::KEY_DOWN)
    {
        Yaw += App->input->GetMouseMotion().x * GetSpeed(MoveType::ROTATION);
        Pitch += App->input->GetMouseMotion().y * GetSpeed(MoveType::ROTATION);
        // Deprecate below
        int mouseMotionX = App->input->GetMouseMotion().x;
        int mouseMotionY = App->input->GetMouseMotion().y;
        Rotate(-0.01 * (float)mouseMotionY, -0.01 * (float)mouseMotionX);
    }

    // Orbit
    // if (App->input->IsModPressed(KMOD_ALT)
    //     && App->input->GetMouseButton().button == SDL_BUTTON_LEFT
    //     && App->input->GetMouseButton().state == SDL_PRESSED)
    // {
    //     OrbitModule();
    // }
}
//
void ModuleCamera::OrbitModule()
{
//     const Model* model = App->renderer->GetCurrentModel();
//     if (model == nullptr)
//     {
//         return;
//     }
//     const float3 moduleOrigin = model->GetOrigin();
//
//     // Radius is the distance to the module in xz plane
//     float2 distanceXZ = float2(Position.x - moduleOrigin.x, Position.z - moduleOrigin.z);
//     const float radius = sqrt((distanceXZ.x * distanceXZ.x) + (distanceXZ.y * distanceXZ.y));
//
//     OrbitAngle += GetSpeed(MoveType::ORBIT);
//     const float3 position = float3(sin(OrbitAngle * DEGTORAD) * radius, Position.y, cos(OrbitAngle * DEGTORAD) * radius);
//     SetPosition(position);
//     Look(moduleOrigin);
}

void ModuleCamera::ZoomInPosition()
{
    Position += CameraFrustum.Front() * GetSpeed(MoveType::ZOOM_POS);
}

void ModuleCamera::ZoomOutPosition()
{
    Position -= CameraFrustum.Front() * GetSpeed(MoveType::ZOOM_POS);
}

inline void ModuleCamera::ZoomOutFOV()
{
    if (HorizontalFovDegree >= 120.0f)
    {
        return;
    }
    HorizontalFovDegree += HorizontalFovDegree * GetSpeed(MoveType::ZOOM_FOV);
}

inline void ModuleCamera::ZoomInFOV()
{
    if (HorizontalFovDegree <= 0.1)
    {
        return;
    }
    HorizontalFovDegree -= HorizontalFovDegree * GetSpeed(MoveType::ZOOM_FOV);
}

inline float ModuleCamera::GetSpeed(MoveType type) const
{
    float speed = 0.0f;
    int mult = 1;
    switch (type)
    {
        case MoveType::TRANSLATION:
            speed = Speed;
            break;
        case MoveType::ROTATION:
            speed = RotationSpeed;
            break;
        case MoveType::ZOOM_POS:
            speed = ZoomPosSpeed;
            break;
        case MoveType::ZOOM_FOV:
            speed = ZoomFovSpeed;
            break;
        case MoveType::ORBIT:
            speed = OrbitSpeed;
            break;
        default:
            speed = Speed;
            break;
    }
    // if (App->input->IsModPressed(KMOD_SHIFT))
    // {
    //     mult = 2;
    // }
    return speed * App->GetDelta() * mult;
}

void ModuleCamera::SetPlaneDistances(const float nearDist, const float farDist)
{
    CameraFrustum.SetViewPlaneDistances(NearDistance = nearDist, FarDistance = farDist);
}

void ModuleCamera::SetDefaultValues()
{
    Init();
}
