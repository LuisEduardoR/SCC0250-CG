/*
 * Copyright 2018 Amanda de Moura Peres
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DM_ADVEN_COLLIDER_HPP
#define DM_ADVEN_COLLIDER_HPP

#include <bitset>
#include <forward_list>
#include <unordered_map>
#include <vector>

#include "../Components/GameObject.hpp"
#include "../Components/Component.hpp"
#include "../Events/Event.hpp"

namespace Adven
{
    class Collider : public Component
    {
        friend class GameObject;
    public:
        using Layer = std::size_t;
        class SceneData final
        {
            friend class Collider;
        private:
            std::forward_list<Collider*> colliders{};
        public:
            std::vector<std::vector<bool>> collisionLayers{};
        };
    private: //Static variables
        static std::unordered_map<const Scene*, SceneData> dataByScene;
    protected: //Static methods
        static void Register(Collider& collider);
        static void Unregister(Collider& collider);
    public: //Static methods
        static void Update();
        static bool CheckCollision(const Collider& a, const Collider& b);
        static SceneData& GetSceneData(const Scene& scene);
    public:
        explicit Collider(Layer layer = 0, bool isTrigger = false);
        ~Collider() override;
    public:
        void Start() override; 
        Event<void(Collider*, Collider*)>& OnCollision();
    private:
        Event<void(Collider*, Collider*)> onCollision{};
    public:
        Layer layer;
        bool isTrigger;
    };
}

#endif /* end of include guard: DM_ADVEN_COLLIDER_HPP */
