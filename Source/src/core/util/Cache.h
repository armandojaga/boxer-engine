#pragma once
#include <unordered_map>
#include <functional>

namespace BoxerEngine
{
    template <typename K, typename V>
    class Cache
    {
    private:
        mutable std::unordered_map<K, V> cache;
        std::function<V(K)> producer;
    public:
        explicit Cache(std::function<V(K)>);
        ~Cache() = default;

        V Get(K&) const;
        V Get(K&& key) const;

        void Clear()
        {
            cache.clear();
        }
    };

    // template implementation
    template <typename K, typename V>
    Cache<K, V>::Cache(std::function<V(K)> producer) : producer(std::move(producer))
    {
    }

    template <typename K, typename V>
    V BoxerEngine::Cache<K, V>::Get(K& key) const
    {
        if(cache.find(key) != cache.end())
        {
            return cache[key];
        }
        auto value = producer(key);
        cache[key] = value;
        return value;
    }

    template <typename K, typename V>
    V Cache<K, V>::Get(K&& key) const
    {
        if (cache.find(std::forward<K>(key)) != cache.end())
        {
            return cache[std::forward<K>(key)];
        }
        auto value = producer(std::forward<K&>(key));
        cache[std::forward<K>(key)] = value;
        return value;
    }
}
