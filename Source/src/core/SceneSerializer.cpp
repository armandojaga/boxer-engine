#include "core/bepch.h"

#include "Scene.h"
#include "SceneSerializer.h"

#include "components/TransformComponent.h"
#include "components/MeshComponent.h"
#include "components/CameraComponent.h"
#include "components/LightComponent.h"
#include "util/YamlDefinitions.h"

#include "modules/ModuleImporter.h"

BoxerEngine::Scene* BoxerEngine::SceneSerializer::Load(const char* path)
{
    if (!Files::IsValidFilePath(path))
    {
        return nullptr;
    }

    YAML::Node sceneNode = YAML::LoadFile(path);

    // Validate scene header
    if (!sceneNode[SCENE_ID].IsDefined() || !sceneNode[SCENE_NAME].IsDefined())
    {
        return nullptr;
    }
    preferences = dynamic_cast<ResourcesPreferences*>(App->preferences->GetPreferenceDataByType(Preferences::Type::RESOURCES));
    const auto sceneOutput = new Scene();
    sceneOutput->SetSceneId(sceneNode[SCENE_ID].as<std::string>());

    if (!sceneNode[CHILD_NODE].IsDefined())
    {
        return sceneOutput;
    }

    for (size_t i = 0; i < sceneNode[CHILD_NODE].size(); ++i)
    {
        LoadEntity(sceneNode[CHILD_NODE][i], sceneOutput);
    }
    return sceneOutput;
}

bool BoxerEngine::SceneSerializer::Save(const Scene* scene, const char* name, const char* path)
{
    YAML::Node scene_data;
    scene_data[SCENE_ID] = scene->GetSceneId();
    scene_data[SCENE_NAME] = scene->GetRoot()->GetName();

    for (int i = 0; i < scene->GetRoot()->GetChildren().size(); ++i)
    {
        scene_data[CHILD_NODE][i] = SaveEntity(scene->GetRoot()->GetChildren()[i]);
    }

    const auto resourcesPreferences = dynamic_cast<ResourcesPreferences*>
        (App->preferences->GetPreferenceDataByType(Preferences::Type::RESOURCES));

    std::string scene_path = path != nullptr ? path : resourcesPreferences->GetAssetsPath(ResourceType::SCENE);
    scene_path.append(name);
    std::ofstream fout(scene_path);
    fout << scene_data;
    return true;
}

YAML::Node BoxerEngine::SceneSerializer::SaveEntity(const Entity* entity)
{
    YAML::Node save_scene;
    save_scene[ENTITY_NAME] = entity->GetName();
    save_scene[ENTITY_ENABLED] = entity->IsEnabled();
    save_scene[ENTITY_ID] = entity->GetId();

    for (int i = 0; i < entity->GetComponents().size(); ++i)
    {
        save_scene[COMPONENT_NODE][i][COMPONENT_NAME] = std::string(entity->GetComponents()[i]->GetName());
        save_scene[COMPONENT_NODE][i][COMPONENT_ENABLED] = entity->GetComponents()[i]->IsEnabled();
        save_scene[COMPONENT_NODE][i][COMPONENT_ID] = entity->GetComponents()[i]->GetId();
        save_scene[COMPONENT_NODE][i][COMPONENT_TYPE] = static_cast<unsigned int>(entity->GetComponents()[i]->GetType());
        save_scene[COMPONENT_NODE][i][COMPONENT_DATA] = SaveComponent(entity->GetComponents()[i]);
    }

    for (int i = 0; i < entity->GetChildren().size(); ++i)
    {
        save_scene[CHILD_NODE][i] = SaveEntity(entity->GetChildren()[i]);
    }

    return save_scene;
}

YAML::Node BoxerEngine::SceneSerializer::SaveComponent(const std::shared_ptr<Component>& component) const
{
    YAML::Node component_node;

    switch (component->GetType())
    {
    case Component::Type::TRANSFORM:
        {
            const auto tc = std::static_pointer_cast<const TransformComponent>(component);

            component_node[POSITION_NODE] = tc->GetPosition();
            component_node[ROTATION_NODE] = tc->GetRotation();
            component_node[SCALE_NODE] = tc->GetScale();

            break;
        }

    case Component::Type::MESH:
        {
            const auto mc = std::static_pointer_cast<const MeshComponent>(component);

            component_node[MODEL_PATH] = mc->GetModelPath();

            for (int i = 0; i < mc->GetMeshesCount(); ++i)
            {
                component_node[MESH_NODE][i][MESH_ENABLED] = mc->IsMeshEnabled(i);

                if (mc->IsMeshTextureLoaded(i))
                {
                    component_node[MESH_NODE][i][MESH_TEXTURE] = mc->GetMeshTextureName(i);
                    component_node[MESH_NODE][i][MESH_TEXTURE_TYPE] = mc->GetMeshTextureType(i);
                }
            }

            break;
        }

    case Component::Type::LIGHT:
        break;

    case Component::Type::CAMERA:
        break;

    default:
        break;
    }

    return component_node;
}

const BoxerEngine::Entity* BoxerEngine::SceneSerializer::LoadEntity(YAML::Node entityNode, Scene* scene, Entity* parent)
{
    Entity* entity = scene->CreateEntity();
    entity->SetName(entityNode[ENTITY_NAME].as<std::string>());
    entity->SetId(entityNode[ENTITY_ID].as<size_t>());

    if (parent)
    {
        entity->SetParent(parent);
    }

    if (entityNode[COMPONENT_NODE].IsDefined())
    {
        for (size_t i = 0; i < entityNode[COMPONENT_NODE].size(); ++i)
        {
            // std::async(std::launch::async, LoadComponent, entityNode[COMPONENT_NODE][i], entity);
            LoadComponent(entityNode[COMPONENT_NODE][i], entity);
        }
    }

    if (entityNode[CHILD_NODE].IsDefined())
    {
        for (size_t i = 0; i < entityNode[CHILD_NODE].size(); ++i)
        {
            LoadEntity(entityNode[CHILD_NODE][i], scene, entity);
        }
    }

    return nullptr;
}

void BoxerEngine::SceneSerializer::LoadComponent(YAML::Node component, Entity* entity) const
{
    switch (static_cast<Component::Type>(component[COMPONENT_TYPE].as<int>()))
    {
    case Component::Type::TRANSFORM:
        {
            entity->CreateComponent<TransformComponent>();
            entity->GetComponent<TransformComponent>()->SetId(component[COMPONENT_ID].as<size_t>());
            entity->GetComponent<TransformComponent>()->SetType(Component::Type::TRANSFORM);
            component[COMPONENT_ENABLED].as<bool>() ? entity->GetComponent<TransformComponent>()->Enable() : entity->GetComponent<TransformComponent>()->Disable();
            entity->GetComponent<TransformComponent>()->SetPosition(component[COMPONENT_DATA][POSITION_NODE].as<float3>());
            entity->GetComponent<TransformComponent>()->SetRotation(component[COMPONENT_DATA][ROTATION_NODE].as<Quat>());
            entity->GetComponent<TransformComponent>()->SetScale(component[COMPONENT_DATA][SCALE_NODE].as<float3>());
            break;
        }
    case Component::Type::MESH:
        {
            entity->CreateComponent<MeshComponent>();
            entity->GetComponent<MeshComponent>()->SetId(component[COMPONENT_ID].as<size_t>());
            entity->GetComponent<MeshComponent>()->SetType(Component::Type::MESH);
            component[COMPONENT_ENABLED].as<bool>() ? entity->GetComponent<MeshComponent>()->Enable() : entity->GetComponent<MeshComponent>()->Disable();

            // if not present in library import from assets folder
            if (!CheckIfImported(component[COMPONENT_DATA][MODEL_PATH].as<std::string>().c_str()))
            {
                ImportFromAssets(component[COMPONENT_DATA][MODEL_PATH].as<std::string>().c_str(), ResourceType::MODEL);
            }

            entity->GetComponent<MeshComponent>()->LoadModel(component[COMPONENT_DATA][MODEL_PATH].as<std::string>().c_str());

            for (int i = 0; i < static_cast<int>(component[COMPONENT_DATA][MESH_NODE].size()); ++i)
            {
                component[COMPONENT_DATA][MESH_NODE][i][MESH_ENABLED].as<bool>()
                    ? entity->GetComponent<MeshComponent>()->EnableMesh(i)
                    : entity->GetComponent<MeshComponent>()->DisableMesh(i);

                if (component[COMPONENT_DATA][MESH_NODE][i][MESH_TEXTURE].IsDefined())
                {
                    if (!CheckIfImported(component[COMPONENT_DATA][MESH_NODE][i][MESH_TEXTURE].as<std::string>().c_str()))
                    {
                        ImportFromAssets(component[COMPONENT_DATA][MESH_NODE][i][MESH_TEXTURE].as<std::string>().c_str(), ResourceType::TEXTURE);
                    }

                    entity->GetComponent<MeshComponent>()->LoadTexture(
                        component[COMPONENT_DATA][MESH_NODE][i][MESH_TEXTURE].as<std::string>().c_str(), i,
                        component[COMPONENT_DATA][MESH_NODE][i][MESH_TEXTURE_TYPE].as<int>());
                }
            }

            break;
        }
    case Component::Type::CAMERA:
        {
            entity->CreateComponent<CameraComponent>();
            entity->GetComponent<CameraComponent>()->SetId(component[COMPONENT_ID].as<size_t>());
            entity->GetComponent<CameraComponent>()->SetType(Component::Type::MESH);
            component[COMPONENT_ENABLED].as<bool>() ? entity->GetComponent<CameraComponent>()->Enable() : entity->GetComponent<CameraComponent>()->Disable();
            break;
        }
    case Component::Type::LIGHT:
        {
            entity->CreateComponent<LightComponent>();
            entity->GetComponent<LightComponent>()->SetId(component[COMPONENT_ID].as<size_t>());
            entity->GetComponent<LightComponent>()->SetType(Component::Type::MESH);
            component[COMPONENT_ENABLED].as<bool>() ? entity->GetComponent<LightComponent>()->Enable() : entity->GetComponent<LightComponent>()->Disable();
            break;
        }
    }
}

void BoxerEngine::SceneSerializer::ImportFromAssets(const char* path, const ResourceType type)
{
    App->importer->ImportAsset(path, type);
}

bool BoxerEngine::SceneSerializer::CheckIfImported(const char* path) const
{
    std::filesystem::path model_name(path);
    model_name = model_name.filename().replace_extension();
    std::string fullPath = preferences->GetLibraryPath(ResourceType::MODEL);
    fullPath.append(model_name.string());

    return Files::IsValidFilePath(fullPath);
}
