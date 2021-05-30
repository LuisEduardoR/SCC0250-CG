/*
 * Copyright 2018 Amanda de Moura Peres
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DM_ADVEN_EVENT_HPP
#define DM_ADVEN_EVENT_HPP

#include <vector>
#include <algorithm>
#include "Listener.hpp"

namespace Adven
{
    template<class T>
    class Event
    {
    private:
        std::vector<Listener<T>*> listeners;
    public:
        void Subscribe(Listener<T>& listener)
        {
            int size = listeners.size();
            listeners.push_back(&listener);
            size = listeners.size();
            listener.events.push_back(this);
        }
        void Unsubscribe(Listener<T>* listener)
        {
            listeners.erase(std::find(listeners.begin(), listeners.end(), listener)); 
        }
        template<class... Args>
        void Raise(Args&&... args)
        {
            int size = listeners.size();
            for (auto listener : listeners)
            {
                listener->function(std::forward<Args>(args)...);
            }
        }
        virtual ~Event()
        {
            for (auto listener : listeners)
            {
                listener->events.erase(std::find(listener->events.begin(), listener->events.end(), this));
            }
        }
    };
}

#endif