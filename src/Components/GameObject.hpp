/*
 * Copyright 2018 Amanda de Moura Peres
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DM_ADVEN_GAMEOBJECT_HPP
#define DM_ADVEN_GAMEOBJECT_HPP

#include "Component.hpp"

#include "../Interfaces/IUpdatable.hpp"

#include <typeinfo>
#include <functional>
#include <memory>
#include <list>

namespace Adven
{
    class GameObject : public IUpdatable
    {
    private:
        std::list<std::unique_ptr<Component>> components;
    public:
        GameObject() = default;
        GameObject(GameObject&& other) = default;

        GameObject& operator=(GameObject&& other) = default;

        ~GameObject() override = default;
    public:
        void Start() override;
        void VDrawUpdate() override;
        void VBlankUpdate() override;
        template<typename T, typename ... Args>
        T& AddComponent(Args&&... args);
        template<typename T>
        T* GetComponent();
        void RemoveComponent(const Component& component);
        void RemoveComponent(std::function<bool(const Component&)> compare);
    };

    template<typename T, typename... Args>
    T& GameObject::AddComponent(Args&&... args)
    {
        components.push_front(std::make_unique<T>(std::forward<Args>(args)...));

        components.front()->gameObject = this;

        return *reinterpret_cast<T*>(components.front().get());
    }
    template<typename T>
    T* GameObject::GetComponent()
    {
        for (auto& c : components)
        {
            T* component = dynamic_cast<T*>(c.get());
            if (component != nullptr)
            {
                return component;
            }
        }
        return nullptr;
    }
}

#endif /* end of include guard: DM_ADVEN_GAMEOBJECT_HPP */