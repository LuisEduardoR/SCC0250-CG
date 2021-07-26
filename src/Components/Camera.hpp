/*
 * Copyright 2018 Amanda de Moura Peres
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DM_ADVEN_CAMERA_HPP
#define DM_ADVEN_CAMERA_HPP

# include "Component.hpp"
# include "../Rendering/Geometry.hpp"
# include "../Rendering/Shader.hpp"
# include "../Rendering/Color.hpp"

union Matrix4x4;

# define AMBIENT_LIGHT_INTENSITY_STEP 2.5f
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
        Camera(bool makeMain, Color ambientLightColor, Mesh skybox);
    public:
        ~Camera() override;
    public:
        /// Clone a camera. Cloning a mainCamera does not make the clone main.
        [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    public:
        [[nodiscard]] Matrix4x4 ViewMatrix() const;
        void RenderSkybox();
    public:

        // Gets the ambient light color modified by intensity.
        Color GetAmbientLightColor();

        // Increases the ambient light intensity.
        void IncreaseAmbientLightIntensity();

        // Decreases the ambient light intensity.
        void DecreaseAmbientLightIntensity();

    private:
        Mesh skybox;
        Color ambientLightColor;
        float ambientLightIntensity;
    };
}

#endif
