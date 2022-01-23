#include "core/bepch.h"
#include "EventManager.h"

void BoxerEngine::EventManager::Publish(Event& event)
{
    auto [start, end] = subscribers.equal_range(event.GetType());
    for (auto i = start; i != end; ++i)
    {
        i->second(event);
    }
}

void BoxerEngine::EventManager::Subscribe(Event::Type type, std::function<void(Event&)>& subscriber)
{
    subscribers.insert(std::make_pair(type, subscriber));
}
