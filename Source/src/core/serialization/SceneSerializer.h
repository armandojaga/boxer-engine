#pragma once

namespace BoxerEngine
{
    class Scene;
    class Entity;
    class Component;

    class SceneSerializer
    {
        friend ModuleScene;

    public:
        SceneSerializer() = default;
        ~SceneSerializer() = default;

        bool Save(const Scene* scene, const char* name, const char* path = nullptr);
    private:
        // Load is private to ensure only ModuleScene can call it 
        // as we retrieve ownership of scene object pointer
        Scene* Load(const char* path);
        YAML::Node SaveEntity(const Entity* entity);
        YAML::Node SaveComponent(const std::shared_ptr<Component>& component) const;
        const Entity* LoadEntity(YAML::Node entityNode, Scene* scene, Entity* parent = nullptr);
        void LoadComponent(YAML::Node component, Entity* entity) const;
        static void ImportFromAssets(const char* path, ResourceType type);
        bool CheckIfImported(const char* path) const;
        ResourcesPreferences* preferences;
    };
}
