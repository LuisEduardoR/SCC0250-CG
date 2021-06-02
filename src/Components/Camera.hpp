/*
 * Copyright 2018 Amanda de Moura Peres
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DM_ADVEN_CAMERA_HPP
#define DM_ADVEN_CAMERA_HPP

#include "Component.hpp"

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
    public:
        ~Camera() override;
    public:
        /// Clone a camera. Cloning a mainCamera does not make the clone main.
        [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    public: 
        [[nodiscard]] Matrix4x4 ViewMatrix() const;
    };
}

#endif
