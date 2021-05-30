/*
 * Copyright 2018 Amanda de Moura Peres
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "adven/GameObject.hpp"
#include <algorithm>

using namespace Adven;

void GameObject::Start()
{
    for (auto& component : components)
        component->Start();
}
void GameObject::VDrawUpdate()
{
    for (auto& component : components)
        component->VDrawUpdate();
}
void GameObject::VBlankUpdate()
{
    for (auto& component : components)
        component->VBlankUpdate();
}

void GameObject::RemoveComponent(const Component& component)
{
    auto compare = [&component](const Component& component2)
    {
         return &component == &component2; 
    };
    RemoveComponent(compare);
}
void GameObject::RemoveComponent(std::function<bool(const Component&)> compare)
{
    auto i = std::find_if(components.cbegin(), components.cend(),
        [&compare](const std::unique_ptr<Component>& component) { return compare(*component);});
    components.erase(i);
}