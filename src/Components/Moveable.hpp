/*
 * Copyright 2018 Amanda de Moura Peres
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DM_ADVEN_MOVEABLE_HPP
#define DM_ADVEN_MOVEABLE_HPP

#include "Component.hpp"

#include "../Math/Vector.hpp"

namespace Adven
{
    class Moveable : public Component
    {
    public:
        Moveable() = default;
        Moveable(Vector3 speed);
        ~Moveable() override = default;
    public:
        [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
        void VDrawUpdate() override;
    public:
        Vector3 speed{};
    };
}

#endif /* end of include guard: DM_ADVEN_MOVEABLE_HPP */
