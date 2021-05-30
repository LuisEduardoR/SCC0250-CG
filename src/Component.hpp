/*
 * Copyright 2018 Amanda de Moura Peres
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DM_ADVEN_COMPONENT_HPP
#define DM_ADVEN_COMPONENT_HPP

#include "IUpdatable.hpp"

namespace Adven
{
    class GameObject;

    class Component : public IUpdatable
    {
        friend class GameObject;
    public:
        ~Component() override = default;
    protected:
        GameObject* gameObject;
    };
}

#endif