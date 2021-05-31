/*
 * Copyright 2018 Amanda de Moura Peres
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DM_ADVEN_LISTENER_HPP
#define DM_ADVEN_LISTENER_HPP

#include <vector>
#include <functional>

namespace Adven
{
    template<class T>
    class Event;
    template<class T>
    class Listener
    {
        friend Event<T>;
    private:
        std::vector<Event<T>*> events;
        std::function<T> function;
    public:
        Listener(std::function<T> function) : function(function) {}
        virtual ~Listener();
    };
}

#include "Event.hpp"

namespace Adven
{    
    template<class T>
    Listener<T>::~Listener()
    {
        for (auto& event : events)
        {
            event->Unsubscribe(this); 
        }
    }
}

#endif /* end of include guard: DM_ADVEN_LISTENER_HPP */