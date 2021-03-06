#pragma once
#include <unordered_map>
#include <functional>

namespace BoxerEngine
{
    template <typename K, typename V>
    class Cache
    {
    public:
        explicit Cache(std::function<V(K)>);
        ~Cache() = default;

        V Get(const K&) const;

        void Clear()
        {
            cache.clear();
        }

    private:
        mutable std::unordered_map<K, V> cache;
        std::function<V(K)> producer;
    };

    // template implementation
    template <typename K, typename V>
    Cache<K, V>::Cache(std::function<V(K)> producer) : producer(std::move(producer))
    {
    }

    template <typename K, typename V>
    V Cache<K, V>::Get(const K& key) const
    {
        // ReSharper disable CppUseAssociativeContains
        if (cache.find(key) != cache.end())
        // ReSharper restore CppUseAssociativeContains
        {
            return cache[key];
        }
        auto value = producer(key);
        cache[key] = value;
        return value;
    }
}
