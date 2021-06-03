/*
 * Copyright 2018 Amanda de Moura Peres
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "GameObject.hpp"
#include "../Scene/Scene.hpp"

#include <algorithm>
#include <cassert>

using namespace Adven;

GameObject::GameObject(const GameObject& other)
{
    // Don't mess with parent only children/components.
    // The parent, conceptually, is not the child's gameobject data.

    for (const GameObject& otherChild : other.children)
    {
        GameObject myChild{ otherChild }; //Copy the child.
        myChild.parent = this;
    }

    for (const std::unique_ptr<Component>& otherComponent : other.components)
    {
        std::unique_ptr<Component> myComponent = otherComponent->Clone();
        myComponent->gameObject = this;
        components.push_back(std::move(myComponent));
    }
}

GameObject::GameObject(GameObject&& other) :
    children(std::move(other.children)), components(std::move(other.components))
{
    // Don't mess with parent only children/components.
    // The parent, conceptually, is not the child's gameobject data.
    
    for (auto& child : children)
    {
        child.parent = this;
    }

    for (auto& component : components)
    {
        component->gameObject = this;
    }
}


GameObject& GameObject::operator=(const GameObject& other)
{
    // Don't mess with parent only children/components.
    // The parent, conceptually, is not the child's gameobject data.

    children.clear();
    components.clear();

    for (const GameObject& otherChild : other.children)
    {
        GameObject myChild{ otherChild }; //Copy the child.
        myChild.parent = this;
    }

    for (const std::unique_ptr<Component>& otherComponent : other.components)
    {
        std::unique_ptr<Component> myComponent = otherComponent->Clone();
        myComponent->gameObject = this;
        components.push_back(std::move(myComponent));
    }

    return *this;
}

GameObject& GameObject::operator=(GameObject&& other)
{
    // Don't mess with parent only children/components.
    // The parent, conceptually, is not the child's gameobject data.

    children = std::move(other.children);
    components = std::move(other.components);

    for (auto& child : children)
    {
        child.parent = this;
    }

    for (auto& component : components)
    {
        component->gameObject = this;
    }

    return *this;
}

GameObject::~GameObject()
{
    if (scene != nullptr)
    {
        auto comparePtr = [this](const GameObject* value)
        {
            return value == this;
        };

        if (auto iter = std::find_if(
                scene->toUpdateObjects.cbegin(),
                scene->toUpdateObjects.cend(), comparePtr);
            iter != scene->toUpdateObjects.cend())
        {
            scene->toUpdateObjects.erase(iter);
        }
    }
}

void GameObject::Start()
{
    for (auto& component : components)
        if (!component->startCalled)
        {
            component->Start();
            component->startCalled = true;
        }
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

void GameObject::AddChild(const GameObject& gameObject)
{
    GameObject copy{ gameObject };
    copy.parent = this;
    children.push_back(copy);
}

void GameObject::AddChild(GameObject&& gameObject)
{
    children.push_back(std::move(gameObject)); 
}

auto GameObject::EraseChild(const GameObject& gameObject) -> std::optional<iterator>
{
    const_iterator iter = std::find_if(children.cbegin(), children.cend(),
        [gameObject](const GameObject& child)
        {
           return &child == &gameObject; 
        });

    if (iter != children.cend())
    {
        return std::optional{ EraseChild(iter) };
    }

    return std::nullopt;
}

auto GameObject::EraseChild(iterator pos) -> iterator
{
    // No need to set parent to nullptr because the child will be destroyed.
    return children.erase(pos); 
}

auto GameObject::EraseChild(const_iterator pos) -> iterator
{
    // No need to set parent to nullptr because the child will be destroyed.
    return children.erase(pos);
}

auto GameObject::Parent() -> GameObject* { return parent; }

auto GameObject::Parent() const -> const GameObject* { return parent; }

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

auto GameObject::GetScene() -> Scene* { return scene; }

auto GameObject::GetScene() const -> const Scene* { return scene; }

auto GameObject::SetScene(Scene* scene) -> void
{
    this->scene = scene;

    scene->toUpdateObjects.push_back(this);
}

auto GameObject::begin() noexcept -> iterator
{
	return children.begin();
}

auto GameObject::begin() const noexcept -> const_iterator
{
	return children.begin();
}

auto GameObject::cbegin() const noexcept -> const_iterator
{
	return children.cbegin();
}

auto GameObject::end() noexcept -> iterator
{
	return children.end();
}

auto GameObject::end() const noexcept -> const_iterator
{
	return children.end();
}

auto GameObject::cend() const noexcept -> const_iterator
{
	return children.cend();
}

auto GameObject::rbegin() noexcept -> reverse_iterator
{
	return children.rbegin();
}

auto GameObject::rbegin() const noexcept -> const_reverse_iterator
{
	return children.rbegin();
}

auto GameObject::crbegin() const noexcept -> const_reverse_iterator
{
	return children.crbegin();
}

auto GameObject::rend() noexcept -> reverse_iterator
{
	return children.rend();
}

auto GameObject::rend() const noexcept -> const_reverse_iterator
{
	return children.rend();
}

auto GameObject::crend() const noexcept -> const_reverse_iterator
{
	return children.crend();
}

