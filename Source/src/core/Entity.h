#pragma once

#include <memory>
#include "util/UUID.h"
#include "components/Component.h"

namespace BoxerEngine
{
    class Entity : public Serializable
    {
    public:
        Entity();
        explicit Entity(Entity* parent);
        ~Entity() override;

        void SetId(UID newId);
        [[nodiscard]] UID GetId() const;

        void SetName(const std::string& newName);
        [[nodiscard]] const std::string& GetName() const;

        void Init();
        void Start();
        void Update();
        void DisplayGizmos() const; // draw the gizmos
        void Draw() const;

        void SetParent(Entity* parent);
        [[nodiscard]] Entity* GetParent() const;

        void AddChild(Entity* child);
        [[nodiscard]] bool HasChildren() const;
        [[nodiscard]] Entity* GetEntity(UID entityId);
        [[nodiscard]] Entity* GetEntity(const std::string& entityName);
        void RemoveChild(UID entityId);
        [[nodiscard]] bool IsChildOf(UID entityId) const;

        template <typename C>
        bool Has();
        template <typename C>
        C* CreateComponent();
        template <typename C>
        [[nodiscard]] C* GetComponent() const;
        template <typename C>
        void RemoveComponent();
        void RemoveComponent(UID componentId);

        void Enable();
        void Disable();
        [[nodiscard]] bool IsEnabled() const;

        [[nodiscard]] std::vector<std::shared_ptr<Component>> GetComponents() const;
        [[nodiscard]] std::vector<Entity*> GetChildren() const;
        void Clear();

        void Save(YAML::Node) override;
        void Load(YAML::Node) override;

    private:
        UID id = 0;
        std::string name{};
        Entity* parent = nullptr;

        bool enabled = true;

        std::vector<std::shared_ptr<Component>> components{};
        std::vector<Entity*> children{};

        [[nodiscard]] bool Has(UID entityId);
        Entity* GetEntity(const std::function<bool(Entity*)>& predicate);
    };

    template <typename C>
    bool Entity::Has()
    {
        auto type = [&](const auto c) { return c->GetType() == C::type; };
        return std::find_if(std::begin(components), std::end(components), type) != std::end(components);
    }

    template <typename C>
    C* Entity::CreateComponent()
    {
        if (!Has<C>())
        {
            std::shared_ptr<C> c = std::make_shared<C>(this);
            components.push_back(c);
            return c.get();
        }
        return nullptr;
    }

    template <typename C>
    C* Entity::GetComponent() const
    {
        auto type = [&](auto c) { return c->GetType() == C::type; };
        auto result = std::find_if(std::begin(components), std::end(components), type);
        if (result != std::end(components))
        {
            return static_cast<C*>(result->get());
        }
        return nullptr;
    }

    template <typename C>
    void Entity::RemoveComponent()
    {
        if (Has<C>())
        {
            auto componentType = [&](const auto c) { return C::type == c->GetType(); };
            components.erase(
                std::remove_if(std::begin(components), std::end(components), componentType),
                components.end()
            );
        }
    }
}
