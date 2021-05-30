/*
 * Copyright 2018 Amanda de Moura Peres
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "adven/Scene.hpp"
#include <algorithm>

using namespace Adven;

Scene* Scene::currentScene = nullptr;

Scene::~Scene(){}
void Scene::Start()
{
    for (GameObject& gameObject : gameObjects)
    {
        gameObject.Start();
    }
}
void Scene::VDrawUpdate()
{
    for (GameObject& gameObject : gameObjects)
    {
        gameObject.VDrawUpdate();
    }
}
void Scene::VBlankUpdate()
{
    for (GameObject& gameObject : gameObjects)
    {
        gameObject.VBlankUpdate();
    }
} 
GameObject& Scene::AddGameObject(GameObject&& gameObject)
{
    gameObjects.push_front(std::move(gameObject));
    return gameObjects.front();
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
    auto i = std::find_if(gameObjects.cbegin(), gameObjects.cend(), compare);
    gameObjects.erase(i);
}