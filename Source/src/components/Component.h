#pragma once
#include "core/util/UUID.h"
#include <memory>

namespace BoxerEngine
{
    class Entity;

    class Component
    {
    public:
        enum class Type
        {
            UNDEFINED,
            TRANSFORM,
            LIGHT,
            CAMERA,
            MESH,
            MATERIAL,
            BOUNDING_BOX,
            AUDIO,
            ANIMATION,
            SCRIPT
        };

        explicit Component(Entity*);
        explicit Component(Type, Entity*);
        virtual ~Component() = default;

        virtual void Init();
        virtual void Start();
        virtual void Update();
        virtual void UpdateUI();
        virtual void DisplayGizmos();

        void SetId(UID id);
        [[nodiscard]] UID GetId() const;

        void Enable();
        void Disable();
        [[nodiscard]] bool IsEnabled() const;

        void SetType(Type type);
        [[nodiscard]] Type GetType() const;

    protected:
        bool enabled = true;
        Type type = Type::UNDEFINED;

    private:
        UID id = 0;
        Entity* parent = nullptr;
    };
}