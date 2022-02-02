#include "SceneSerializer.h"

#include "Scene.h"
#include "Entity.h"
#include "components/Component.h"
#include "components/TransformComponent.h"
#include "components/MeshComponent.h"
#include "components/CameraComponent.h"
#include "components/LightComponent.h"
#include "util/YamlDefinitions.h"

#include "Application.h"
#include "modules/ModuleImporter.h"

BoxerEngine::Scene* BoxerEngine::SceneSerializer::Load(const char* path)
{
	if (!BoxerEngine::Files::IsValidFilePath(path))
	{
		return nullptr;
	}

	YAML::Node scene_node = YAML::LoadFile(path);
	
	// Validate scene header
	if (!scene_node[SCENE_ID].IsDefined() || !scene_node[SCENE_NAME].IsDefined())
	{
		return nullptr;
	}
	preferences = static_cast<ResourcesPreferences*>(App->preferences->GetPreferenceDataByType(Preferences::Type::RESOURCES));
	Scene* scene_output = new Scene();
	scene_output->SetSceneId(std::move(scene_node[SCENE_ID].as<std::string>()));
	
	if (!scene_node[CHILD_NODE].IsDefined())
	{
		return scene_output;
	}

	for (int i = 0; i < scene_node[CHILD_NODE].size(); ++i)
	{
		LoadEntity(scene_node[CHILD_NODE][i], scene_output);
	}
	return scene_output;
}

bool BoxerEngine::SceneSerializer::Save(const Scene* scene, const char* name, const char* path)
{
	YAML::Node scene_data;
	scene_data[SCENE_ID] = scene->GetSceneId();
	scene_data[SCENE_NAME] = scene->GetRoot()->GetName();

	for (int i = 0; i < scene->GetRoot()->GetChildren().size(); ++i)
	{
		scene_data[CHILD_NODE][i] = std::move(SaveEntity(scene->GetRoot()->GetChildren()[i]));
	}
	
	BoxerEngine::ResourcesPreferences* preferences = static_cast<BoxerEngine::ResourcesPreferences*>
    	(App->preferences->GetPreferenceDataByType(BoxerEngine::Preferences::Type::RESOURCES));
	
	std::string scene_path = path != nullptr ? path : preferences->GetAssetsPath(BoxerEngine::ResourceType::SCENE);
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
		save_scene[COMPONENT_NODE][i][COMPONENT_DATA] = std::move(SaveComponent(entity->GetComponents()[i]));
	}

    for (int i = 0; i < entity->GetChildren().size(); ++i)
    {
        save_scene[CHILD_NODE][i] = std::move(SaveEntity(entity->GetChildren()[i]));
    }

    return save_scene;
}

YAML::Node BoxerEngine::SceneSerializer::SaveComponent(const std::shared_ptr<BoxerEngine::Component> component)
{
	YAML::Node component_node;

	switch (component->GetType())
	{
		case Component::Type::TRANSFORM:
		{

			auto tc = std::static_pointer_cast<const BoxerEngine::TransformComponent>(component);

			component_node[POSITION_NODE][NODE_X] = tc->GetPosition().x;
			component_node[POSITION_NODE][NODE_Y] = tc->GetPosition().y;
			component_node[POSITION_NODE][NODE_Z] = tc->GetPosition().z;
			
			component_node[ROTATION_NODE][NODE_X] = tc->GetRotation().x;
			component_node[ROTATION_NODE][NODE_Y] = tc->GetRotation().y;
			component_node[ROTATION_NODE][NODE_Z] = tc->GetRotation().z;
			component_node[ROTATION_NODE][NODE_W] = tc->GetRotation().w;

			component_node[SCALE_NODE][NODE_X] = tc->GetScale().x;
			component_node[SCALE_NODE][NODE_Y] = tc->GetScale().y;
			component_node[SCALE_NODE][NODE_Z] = tc->GetScale().z;

			break;
		}
			
		case Component::Type::MESH:
		{
			auto mc = std::static_pointer_cast<const BoxerEngine::MeshComponent>(component);

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

const BoxerEngine::Entity* BoxerEngine::SceneSerializer::LoadEntity(YAML::Node entity_node, Scene* scene, Entity* parent)
{
	Entity* entity = scene->CreateEntity();
	entity->SetName(std::move(entity_node[ENTITY_NAME].as<std::string>()));
	entity->SetId(entity_node[ENTITY_ID].as<size_t>());

	if (parent)
	{
		entity->SetParent(parent);
	}

	if (entity_node[COMPONENT_NODE].IsDefined())
	{
		for (int i = 0; i < entity_node[COMPONENT_NODE].size(); ++i)
		{
			LoadComponent(entity_node[COMPONENT_NODE][i], entity);
		}
	}

	if (entity_node[CHILD_NODE].IsDefined())
	{
		for (int i = 0; i < entity_node[CHILD_NODE].size(); ++i)
		{
			LoadEntity(entity_node[CHILD_NODE][i], scene, entity);
		}
	}

	return nullptr;
}

void BoxerEngine::SceneSerializer::LoadComponent(YAML::Node component, Entity* entity)
{
	switch (static_cast<Component::Type>(component[COMPONENT_TYPE].as<int>()))
	{
		case Component::Type::TRANSFORM:
		{
			entity->CreateComponent<TransformComponent>();
			entity->GetComponent<TransformComponent>()->SetId(component[COMPONENT_ID].as<size_t>());
			entity->GetComponent<TransformComponent>()->SetType(Component::Type::TRANSFORM);
			component[COMPONENT_ENABLED].as<bool>() ? entity->GetComponent<TransformComponent>()->Enable() :
				entity->GetComponent<TransformComponent>()->Disable();
			entity->GetComponent<TransformComponent>()->SetPosition(Yaml::ToFloat3(component[COMPONENT_DATA][POSITION_NODE]));
			entity->GetComponent<TransformComponent>()->SetRotation(Yaml::ToFloat4(component[COMPONENT_DATA][ROTATION_NODE]));
			entity->GetComponent<TransformComponent>()->SetScale(Yaml::ToFloat3(component[COMPONENT_DATA][SCALE_NODE]));
			break;
		}
		case Component::Type::MESH:
		{
			entity->CreateComponent<MeshComponent>();
			entity->GetComponent<MeshComponent>()->SetId(component[COMPONENT_ID].as<size_t>());
			entity->GetComponent<MeshComponent>()->SetType(Component::Type::MESH);
			component[COMPONENT_ENABLED].as<bool>() ? entity->GetComponent<MeshComponent>()->Enable() :
				entity->GetComponent<MeshComponent>()->Disable();

			// if not present in library import from assets folder
			if (!CheckIfImported(component[COMPONENT_DATA][MODEL_PATH].as<std::string>().c_str()))
			{
				ImportFromAssets(component[COMPONENT_DATA][MODEL_PATH].as<std::string>().c_str(), ResourceType::MODEL);
			}
			
			entity->GetComponent<MeshComponent>()->LoadModel(component[COMPONENT_DATA][MODEL_PATH].as<std::string>().c_str());
			
			for (int i = 0; i < component[COMPONENT_DATA][MESH_NODE].size(); ++i)
			{
				component[COMPONENT_DATA][MESH_NODE][i][MESH_ENABLED].as<bool>()
					? entity->GetComponent<MeshComponent>()->EnableMesh(i) : entity->GetComponent<MeshComponent>()->DisableMesh(i);
				
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
			component[COMPONENT_ENABLED].as<bool>() ? entity->GetComponent<CameraComponent>()->Enable() :
				entity->GetComponent<CameraComponent>()->Disable();
			break;
		}
		case Component::Type::LIGHT:
		{
			entity->CreateComponent<LightComponent>();
			entity->GetComponent<LightComponent>()->SetId(component[COMPONENT_ID].as<size_t>());
			entity->GetComponent<LightComponent>()->SetType(Component::Type::MESH);
			component[COMPONENT_ENABLED].as<bool>() ? entity->GetComponent<LightComponent>()->Enable() :
				entity->GetComponent<LightComponent>()->Disable();
			break;
		}
	}
}

void BoxerEngine::SceneSerializer::ImportFromAssets(const char* path, ResourceType type)
{
	App->importer->ImportAsset(path, type);
}

bool BoxerEngine::SceneSerializer::CheckIfImported(const char* path)
{
	std::filesystem::path model_name(path);
	model_name = model_name.filename().replace_extension();
	std::string full_path = preferences->GetLibraryPath(ResourceType::MODEL);
	full_path.append(model_name.string());

	return Files::IsValidFilePath(full_path);
}
