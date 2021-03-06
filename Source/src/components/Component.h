#pragma once
#include "core/serialization/Serializable.h"
#include "core/util/UUID.h"

namespace BoxerEngine
{
    class Entity;

    class Component: public Serializable
    {
    public:
        enum class Type
        {
            UNDEFINED = 0,
            TRANSFORM,
            LIGHT,
            CAMERA,
            MESH,
            MODEL,
            MATERIAL,
            BOUNDING_BOX,
            AUDIO,
            ANIMATION,
            SCRIPT,
            COUNT
        };

        explicit Component(Entity* entity);
        explicit Component(Type type, Entity* entity);
        ~Component() override = default;

        virtual void Init();
        virtual void Start();
        virtual void Update();
        virtual void UpdateUI();
        virtual void DisplayGizmos();
        virtual void Draw();

        void SetId(UID id);
        [[nodiscard]] UID GetId() const;

        void Enable();
        void Disable();
        [[nodiscard]] bool IsEnabled() const;

        void SetType(Type type);
        [[nodiscard]] Type GetType() const;

        [[nodiscard]] Entity* GetEntity() const;

        [[nodiscard]] virtual const char* GetName() const = 0;

        // void Save(YAML::Node){};
        // void Load(YAML::Node){};

    protected:
        bool enabled = true;
        Type type = Type::UNDEFINED;

    private:
        UID id = 0;
        Entity* entity = nullptr;
    };
}
