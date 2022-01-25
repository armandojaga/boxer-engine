#pragma once
#include "Entity.h"

namespace BoxerEngine
{
    class Scene
    {
    public:
        Scene();
        ~Scene();

        void Init();
        void Start();
        void Update();

        Entity* CreateEntity();
        void InitRoot();
        void Clear();

        void SetSceneId(const std::string&);
        [[nodiscard]] const std::string& GetSceneId() const;

        [[nodiscard]] bool IsLoaded() const;

        [[nodiscard]] Entity* GetRoot() const;

    private:
        std::string id;
        Entity* root = nullptr;
        bool loaded = false;
    };
}
