/*
 * Copyright 2018 Amanda de Moura Peres
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "Moveable.hpp"
#include "Transform.hpp"
#include "GameObject.hpp"
#include "../Time/Time.hpp"
#include "../Math/Matrix4x4.hpp"

#include <iostream>

using namespace Adven;

Moveable::Moveable(Vector3 speed) : speed(speed) {}

auto Moveable::Clone() const -> std::unique_ptr<Component>
{
    return std::make_unique<Moveable>(speed);
}

void Moveable::VDrawUpdate()
{
    auto* transform = GetGameObject()->GetComponent<Transform>();

    if (!transform)
    {
        std::cout << "Moveable expects a Transform";
        return;
    }

    transform->localPosition += Vector3 {
        Matrix4x4::Rotate(transform->localRotation)
        * Vector4{ speed, 1.0f }
        * Time::DeltaTime
    };
}
