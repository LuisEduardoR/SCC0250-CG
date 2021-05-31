/*
 * Copyright 2018 Amanda de Moura Peres
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

/*
    This file contains the base class to handle a scene
*/

#ifndef DM_ADVEN_SCENE_HPP
#define DM_ADVEN_SCENE_HPP

#include "../Interfaces/IUpdatable.hpp"
#include "../Components/GameObject.hpp"

#include <list>

namespace Adven
{
    class Scene : IUpdatable
    {
        friend class GameObject;
    public:
        static Scene* currentScene;
    public:
        template<typename T>
        static void LoadScene()
        {
            delete currentScene;
            currentScene = new T();
            currentScene->Start();
        }
    private:
        std::list<GameObject> gameObjects;
    public:
        virtual ~Scene() = default;
        virtual void Start() final override;
        virtual void VDrawUpdate() final override;
        virtual void VBlankUpdate() final override;
        GameObject& AddGameObject(GameObject&& gameObject);
        void RemoveGameObject(const GameObject& gameObject);
        void RemoveGameObject(std::function<bool(const GameObject&)> compare);
    };
}

#endif /* end of include guard: DM_ADVEN_SCENE_HPP */