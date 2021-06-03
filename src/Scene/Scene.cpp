/*
 * Copyright 2018 Amanda de Moura Peres
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "Scene.hpp"

#include <algorithm>
#include <utility>

#include "../Components/GameObject.hpp"

using namespace Adven;

Scene* Scene::currentScene = nullptr;

void Scene::Start()
{
    for (GameObject* gameObject : toUpdateObjects)
    {
        gameObject->Start();
    }
}

void Scene::VDrawUpdate()
{
    for (GameObject* gameObject : toUpdateObjects)
    {
        gameObject->VDrawUpdate();
    }
}

void Scene::VBlankUpdate()
{
    for (GameObject* gameObject : toUpdateObjects)
    {
        gameObject->VBlankUpdate();
    }
} 

GameObject& Scene::AddGameObject(GameObject&& gameObject)
{
    rootObjects.push_back(std::move(gameObject));
    rootObjects.back().SetScene(this);
    return rootObjects.back();
}

void Scene::RemoveGameObject(const GameObject& gameObject)
{
    auto compare = [&gameObject](const GameObject& gameObject2)
    {
         return &gameObject == &gameObject2; 
    };
    RemoveGameObject(compare);
}

void Scene::RemoveGameObject(std::function<bool(const GameObject& gameObject)> compare)
{
    auto i = std::find_if(rootObjects.cbegin(), rootObjects.cend(), compare);
    rootObjects.erase(i);
}
