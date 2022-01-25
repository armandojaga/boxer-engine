#pragma once

struct SelectionChangedEventPayload
{
    explicit SelectionChangedEventPayload(BoxerEngine::Entity* selected) : selected(selected)
    {
    }

    [[nodiscard]] BoxerEngine::Entity* GetSelected() const
    {
        return selected;
    }

private:
    BoxerEngine::Entity* selected;
};