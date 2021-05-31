/*
 * Copyright 2018 Amanda de Moura Peres
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DM_ADVEN_CAMERA_HPP
#define DM_ADVEN_CAMERA_HPP

#include "Component.hpp"
#include "GameObject.hpp"

union Matrix4x4;

namespace Adven
{
    class Camera : public Component
    {
    private:
        static Camera* mainCamera;
    public:
        // Returns the main camera if there's one. nullptr if not.
        static Camera* MainCamera();
        // Sets or clears the main camera. nullptr to clear.
        static void MainCamera(Camera* camera);
    public:
        Camera(bool makeMain = false);
        Camera(const Camera& camera) = default;
        Camera& operator=(const Camera& camera) = default;

        virtual ~Camera();
    public: 
        [[nodiscard]] Matrix4x4 ViewMatrix() const;
    };
}

#endif
