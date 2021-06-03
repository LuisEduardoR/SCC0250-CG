/*
 * Copyright 2018 Amanda de Moura Peres
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DM_ADVEN_COMPONENT_HPP
#define DM_ADVEN_COMPONENT_HPP

#include <memory>

#include "../Interfaces/IUpdatable.hpp"

namespace Adven
{
    class GameObject;

    class Component : public IUpdatable
    {
        friend class GameObject;
    public:
        Component() = default;
        // No copy or move constructors on a virtual class.
        // It can cause unexpected behaviour, such as copying
        // an object by a base class reference and "losing"
        // the derived classes.
        Component(const Component& other) = delete;
        Component(Component&& other) = delete;
        auto operator=(const Component& other) = delete;
        auto operator=(Component&& other) = delete;
    public:
        // Virtual destructor. REQUIRED in all virtual (base and derived) classes.
        ~Component() override = default;
    public:
        [[nodiscard]] auto GetGameObject() const -> const GameObject*;
        [[nodiscard]] auto GetGameObject() -> GameObject*;
    private:
        /// Clones an component.
        /// Meant for making prefab gameobjects.
        [[nodiscard]] virtual auto Clone() const -> std::unique_ptr<Component> = 0;
    private:
        GameObject* gameObject{ nullptr };
    private:
        bool startCalled{ false };
    };
}

#endif /* end of include guard: DM_ADVEN_COMPONENT_HPP */
