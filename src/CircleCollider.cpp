/*
 * Copyright 2018 Amanda de Moura Peres
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "adven/CircleCollider.hpp"
#include "adven/GameObject.hpp"
#include "Transform.hpp"

using namespace Adven;

bool CircleCollider::CheckCollision(const CircleCollider& a, const CircleCollider& b)
{
    const auto* aTransform = a.gameObject->GetComponent<Transform>();
    const auto* bTransform = b.gameObject->GetComponent<Transform>();
    Vector3 distance = aTransform->WorldPosition() - bTransform->WorldPosition();

    return std::pow(a.radius + b.radius, 2)
        >= std::pow(distance.x, 2) + std::pow(distance.y, 2);
}

CircleCollider::CircleCollider(float radius, bool isTrigger) : Collider(isTrigger), radius(radius)
{
    Register(*this);
}
CircleCollider::~CircleCollider()
{
    Unregister(*this);
}
void CircleCollider::Start() {}
void CircleCollider::VDrawUpdate() {}
void CircleCollider::VBlankUpdate() {}