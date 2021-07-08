/*
 * Copyright 2018 Amanda de Moura Peres
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "ItemAnimator.hpp"
#include "Transform.hpp"
#include "GameObject.hpp"
#include "../Time/Time.hpp"
#include "../Math/Matrix4x4.hpp"
#include "../Rendering/Geometry.hpp"

#include <iostream>

using namespace Adven;

ItemAnimator::ItemAnimator(float amplitude, float frequency) : amplitude(amplitude), frequency(frequency), originalYPos(0.0f), savedOriginalPos(false) {}

auto ItemAnimator::Clone() const -> std::unique_ptr<Component>
{
    return std::make_unique<ItemAnimator>(amplitude, frequency);
}

void ItemAnimator::VDrawUpdate()
{

    auto* transform = GetGameObject()->GetComponent<Transform>();


    if (!transform)
    {
        std::cout << "ItemAnimator expects a Transform";
        return;
    }

    if(!savedOriginalPos)
    {
        savedOriginalPos = true;
        originalYPos = transform->localPosition.y;
    }

    auto t = 2.0f * CONST_PI * frequency * Time::Time;
    transform->localRotation.y = t;
    transform->localPosition.y = originalYPos + (amplitude * sinf(t));

}
