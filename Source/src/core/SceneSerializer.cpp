#include "SceneSerializer.h"

#include "Scene.h"
#include "components/Component.h"
#include "components/TransformComponent.h"
#include "components/MeshComponent.h"
#include "util/YamlDefinitions.h"

const BoxerEngine::Scene* BoxerEngine::SceneSerializer::Load(std::filesystem::path& path)
{
	if (!BoxerEngine::Files::IsValidFilePath(path))
	{
		return nullptr;
	}

	YAML::Node scene_node = YAML::LoadFile(path.string().c_str());
	
	// Validate scene header
	if (!scene_node[SCENE_ID].IsDefined())
	{
		return nullptr;
	}

	Scene* scene_output = new Scene();
	scene_output->SetSceneId(std::move(scene_node[SCENE_ID].as<std::string>()));
	
	if (!scene_node[ENTITY_ROOT].IsDefined())
	{
		return scene_output;
	}

	LoadEntity(scene_node[ENTITY_ROOT], scene_output);
	return scene_output;
}

bool BoxerEngine::SceneSerializer::Save(const Scene* scene, const char* name, const char* path)
{
	YAML::Node scene_data;
	scene_data[SCENE_ID] = scene->GetSceneId();
	scene_data[ENTITY_ROOT] = SaveEntity(scene->GetRoot());
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

			component_node[SCALE_NODE][NODE_X] = tc->GetScale().x;
			component_node[SCALE_NODE][NODE_Y] = tc->GetScale().y;
			component_node[SCALE_NODE][NODE_Z] = tc->GetScale().z;

			break;
		}
			
		case Component::Type::MESH:
		{
			auto mc = std::static_pointer_cast<const BoxerEngine::MeshComponent>(component);

			component_node[MODEL_PATH] = mc->GetModelName();
			
			for (int i = 0; i < mc->GetMeshesCount(); ++i)
			{
				component_node[MESH_NODE][i][MESH_ENABLED] = mc->IsMeshEnabled(i);
				
				if (mc->IsMeshTextureLoaded(i))
				{
					component_node[MESH_NODE][i][MESH_TEXTURE] = mc->GetMeshTextureName(i);
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

const BoxerEngine::Entity* BoxerEngine::SceneSerializer::LoadEntity(YAML::Node entity, Scene* scene)
{
	return nullptr;
}

const std::shared_ptr<BoxerEngine::Component> BoxerEngine::SceneSerializer::LoadComponent(YAML::Node& component)
{
	return std::shared_ptr<BoxerEngine::Component>();
}
