#pragma once
#include <variant>
#include "core/util/UUID.h"
#include "Math/float3x3.h"

namespace BoxerEngine
{
    //event payloads created here because std::variant does not like forward declarations
    struct SelectionChangedEventPayload
    {
        explicit SelectionChangedEventPayload(Entity* selected): selected(selected)
        {
        }

        [[nodiscard]] Entity* GetSelected() const
        {
            return selected;
        }

    private:
        Entity* selected;
    };

    struct TransformChangedEventPayload
    {
        TransformChangedEventPayload(const float3x3& transform): transform(transform)
        {
        }

        [[nodiscard]] float3x3 GetTransform() const
        {
            return transform;
        }

    private:
        float3x3 transform;
    };

    //std::monostate is added just so we can have an empty std::variant
    using EventData = std::variant<std::monostate, SelectionChangedEventPayload, TransformChangedEventPayload>;

    class Event
    {
    public:
        enum class Type
        {
            UNDEFINED = 0,
            SELECTION_CHANGED,
            TRANSFORM_CHANGED,
            MAX
        };

        explicit Event(Type type);

        [[nodiscard]] Type GetType() const
        {
            return type;
        }

        template <typename T, typename ...Args>
        void SetEventData(Args ...);

        template <typename T>
        T& GetEventData();


    private:
        Type type = Type::UNDEFINED;
        EventData data;
    };

    inline Event::Event(Type type): type(type)
    {
        data = std::monostate{};
    }

    template <typename T, typename ... Args>
    void Event::SetEventData(Args ... args)
    {
        data.emplace<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    T& Event::GetEventData()
    {
        return std::get<T>(data);
    }
}
