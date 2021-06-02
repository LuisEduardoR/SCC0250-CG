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
#include <optional>

namespace Adven
{
    class Scene;

    class GameObject final : public IUpdatable
    {
    private:
        GameObject* parent{ nullptr };
        // No unique_ptr needed because GameObject is final.
        std::list<GameObject> children{};
        // unique_ptr because Component is polymorphic.
        std::list<std::unique_ptr<Component>> components{};
    public:
        using value_type                = decltype(children)::value_type;
        using reference                 = decltype(children)::reference;
        using const_reference           = decltype(children)::const_reference;
        using size_type                 = decltype(children)::size_type;
        using difference_type           = decltype(children)::difference_type;
        using iterator                  = decltype(children)::iterator;
        using const_iterator            = decltype(children)::const_iterator;
        using reverse_iterator          = decltype(children)::reverse_iterator;
        using const_reverse_iterator    = decltype(children)::const_reverse_iterator;
    public:
        GameObject() = default;

        /// Construct a GameObject with a copy of the children
        /// and components from other. Parent is not copied.
        GameObject(const GameObject& other);

        /// Construct a GameObject by moving the chilren and 
        /// components from other.
        /// Parent is not moved, other is left in empty state
        /// but is not removed from it's parent if any.
        GameObject(GameObject&& other);

        /// Assign children and components by copying from other.
        /// Any existing children and components are cleared.
        /// Current parent is not modified.
        GameObject& operator=(const GameObject& other);

        /// Assign children and components by moving from other.
        /// Any existing children and components are cleared.
        /// Parent is not moved, other is left in empty state
        /// but is not removed from it's parent if any.
        GameObject& operator=(GameObject&& other);

        ~GameObject() override = default;
    public:
        void Start() override;
        void VDrawUpdate() override;
        void VBlankUpdate() override;
    public:
        /// Copies gameobject, and adds copy as a child.
        void AddChild(const GameObject& gameObject);

        /// Moves gameobject, and adds it as a child.
        void AddChild(GameObject&& gameObject);

        /// Erases this exact gameobject (pointer comparsion).
        /// If object is found:
        /// Returns an iterator following the object that was removed.
        auto EraseChild(const GameObject& gameObject) -> std::optional<iterator>;
        
        /// Erases the child at pos.
        /// Returns an iterator following the object that was removed.
        auto EraseChild(iterator pos) -> iterator;
        
        /// Erases the child at pos.
        /// Returns an iterator following the object that was removed.
        auto EraseChild(const_iterator pos) -> iterator;

        template<typename T, typename ... Args>
        T& AddComponent(Args&&... args);
        template<typename T>
        T* GetComponent();
        template<typename T>
        const T* GetComponent() const;
        GameObject* Parent();
        const GameObject* Parent() const;
        void RemoveComponent(const Component& component);
        void RemoveComponent(std::function<bool(const Component&)> compare);
    public: // Container methods.
        auto begin() noexcept -> iterator;
        auto begin() const noexcept -> const_iterator;
        auto cbegin() const noexcept -> const_iterator;
        auto end() noexcept -> iterator;
        auto end() const noexcept -> const_iterator;
        auto cend() const noexcept -> const_iterator;
        auto rbegin() noexcept -> reverse_iterator;
        auto rbegin() const noexcept -> const_reverse_iterator;
        auto crbegin() const noexcept -> const_reverse_iterator;
        auto rend() noexcept -> reverse_iterator;
        auto rend() const noexcept -> const_reverse_iterator;
        auto crend() const noexcept -> const_reverse_iterator;
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

    template<typename T>
    const T* GameObject::GetComponent() const
    {
        for (auto& c : components)
        {
            const T* component = dynamic_cast<const T*>(c.get());
            if (component != nullptr)
            {
                return component;
            }
        }
        return nullptr;
    }
}

#endif /* end of include guard: DM_ADVEN_GAMEOBJECT_HPP */
