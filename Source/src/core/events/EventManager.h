#pragma once

#include "Event.h"
#include <map>
#include <functional>

namespace BoxerEngine
{
    // right now we use blocking events (dispatched synchronously)
    class EventManager
    {
    public:
        void Publish(Event& event);
        void Subscribe(Event::Type type, std::function<void(Event&)>& subscriber);

    private:
        EventManager() = default;
        std::multimap<Event::Type, std::function<void(Event&)>> subscribers{};

    public:
        static EventManager& GetInstance()
        {
            static EventManager instance;
            return instance;
        }

        EventManager& operator=(const EventManager&) = delete;
        EventManager& operator=(EventManager&&) = delete;
        EventManager(const EventManager&) = delete;
    };
}
