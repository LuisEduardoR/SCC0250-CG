/*
 * Copyright 2018 Amanda de Moura Peres
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DM_ADVEN_CIRCLECOLLIDER_HPP
#define DM_ADVEN_CIRCLECOLLIDER_HPP

#include "Collider.hpp"

namespace Adven
{
    class CircleCollider : public Collider
    {
        friend class GameObject;
    public:
        static bool CheckCollision(const CircleCollider& a, const CircleCollider& b);
    public:
        float radius;
    public:
        CircleCollider(float radius, bool isTrigger = false);
        virtual ~CircleCollider() = default;
    public:
        /// Clones the transform.
        /// This function does not clone the transform childs nor parent.
        [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    };
}

#endif /* end of include guard: DM_ADVEN_CIRCLECOLLIDER_HPP */
