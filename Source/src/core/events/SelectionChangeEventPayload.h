#pragma once

#include "core/Entity.h"

namespace BoxerEngine
{
    struct SelectionChangedEventPayload
    {
        explicit SelectionChangedEventPayload(Entity* selected) : selected(selected)
        {
        }

        [[nodiscard]] Entity* GetSelected() const
        {
            return selected;
        }

    private:
        Entity* selected;
    };
}
