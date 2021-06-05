/*
 * Copyright 2018 Amanda de Moura Peres
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "Exceptions.hpp"

using namespace Adven;

Adven::NotImplementedException::NotImplementedException() : std::logic_error("Function not implemented") {}