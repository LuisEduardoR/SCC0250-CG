/*
 * Copyright 2018 Amanda de Moura Peres
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "Collider.hpp"
//#include "RectCollider.hpp"
#include "CircleCollider.hpp"
#include "../Components/Moveable.hpp"
#include "../Components/Transform.hpp"
#include "../Time/Time.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>

using namespace Adven;

std::unordered_map<const Scene*, Collider::SceneData> Collider::dataByScene;
/*
    Static methods
*/
void Collider::Register(Collider& collider)
{
    if (Scene* scene = collider.GetGameObject()->GetScene())
    {
        // If there's no list for this scene insert it.
        // Otherwise do nothing.
        auto [iter, _didInsert] = dataByScene.insert({ scene, {} });
        auto& [key, data] = *iter;

        data.colliders.push_front(&collider);
    }
}

void Collider::Unregister(Collider& collider)
{
    if (Scene* scene = collider.GetGameObject()->GetScene())
    {
        if (auto iter = dataByScene.find(scene); iter != dataByScene.end())
        {
            iter->second.colliders.remove(&collider);
        }
    }
}

void Collider::Update()
{
    for (auto& [scene, data] : dataByScene)
    {
        for (auto i = data.colliders.begin(); i != data.colliders.end(); ++i)
        {
            for (auto j = ++data.colliders.begin(); j != data.colliders.end(); ++j)
            {
                if (i == j) continue;

                auto* colliderI = *i;
                auto* colliderJ = *j;

                try
                {
                    bool shouldCollide = data.collisionLayers
                        .at(colliderI->layer)
                        .at(colliderJ->layer);

                    if (!shouldCollide) continue;
                }
                catch (const std::out_of_range&)
                {
                    //Assume the objects should collide.
                }

                if (CheckCollision(*colliderI, *colliderJ))
                {
                    colliderI->onCollision.Raise(colliderI, colliderJ);
                    colliderJ->onCollision.Raise(colliderJ, colliderI);
                    
                    if (!colliderJ->isTrigger && !colliderI->isTrigger)
                    {
                        Moveable* mc = colliderI->GetGameObject()->GetComponent<Moveable>();
                        Transform* tc = colliderI->GetGameObject()->GetComponent<Transform>();
                        if (mc)
                        {
                            tc->localPosition -= mc->speed * Time::DeltaTime;
                            mc->speed = Vector3();
                        }

                        Moveable* ml = colliderJ->GetGameObject()->GetComponent<Moveable>();
                        Transform* tl = colliderJ->GetGameObject()->GetComponent<Transform>();
                        if (ml)
                        {
                            tl->localPosition -= ml->speed * Time::DeltaTime;
                            ml->speed = Vector3();
                        }
                    }
                }
            }
        }
    }
}

bool Collider::CheckCollision(const Collider& a, const Collider& b)
{
    //if (typeid(a) == typeid(RectCollider) && typeid(b) == typeid(RectCollider))
    //    return RectCollider::CheckCollision(reinterpret_cast<const RectCollider&>(a), reinterpret_cast<const RectCollider&>(b));
    if (typeid(a) == typeid(CircleCollider) && typeid(b) == typeid(CircleCollider))
        return CircleCollider::CheckCollision(reinterpret_cast<const CircleCollider&>(a), reinterpret_cast<const CircleCollider&>(b));
    else
    {
        //Debug::Error("Collider::CheckCollision failed to identify collider type");
        return false;
    }
}


Collider::SceneData& Collider::GetSceneData(const Scene& scene)
{
    auto [iter, didInsert] = dataByScene.insert({ &scene, {} });
    return iter->second;
}


Collider::Collider(Layer layer, bool isTrigger) : layer(layer), isTrigger(isTrigger) {}

void Collider::Start()
{
    Register(*this);
}

Collider::~Collider()
{
    Unregister(*this);
}

Event<void(Collider*, Collider*)>& Collider::OnCollision()
{
    return onCollision;    
}
