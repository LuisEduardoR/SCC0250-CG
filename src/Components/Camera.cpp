/*
 * Copyright 2018 Amanda de Moura Peres
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "Camera.hpp"

#include "../Math/Matrix4x4.hpp"
#include "Transform.hpp"
#include "GameObject.hpp"
#include "../Rendering/Renderer.hpp"
#include "../WindowSystem/WindowSystem.hpp"

namespace Adven
{

Camera* Camera::mainCamera = nullptr;
/**
 * Static methods
 */
Camera* Camera::MainCamera()
{
    return mainCamera;
}
void Camera::MainCamera(Camera* camera)
{
    mainCamera = camera;
}
/**
 * Instance methods
 */
Camera::Camera(bool makeMain, Mesh skybox, std::shared_ptr<Shader> skyboxShader) : skybox(skybox), skyboxShader(skyboxShader)
{
    if (makeMain)
    {
        mainCamera = this;
    }
}
Camera::~Camera()
{
    if (this == mainCamera)
    {
        mainCamera = nullptr;
    }
}

void Camera::RenderSkybox()
{
    Renderer::SetProgram(*skyboxShader.get());
    auto* transform = GetGameObject()->GetComponent<Transform>();
    Renderer::SetViewMatrix(Matrix4x4::Camera({}, transform->WorldRotation(),
        { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }));

    // Gets the data for rendering (positions and UVs)
    const std::vector<Mesh::VertexInput>& vertexInputBuffer(
        skybox.GetVertexInput()
    );

    // Draws each face of an object
    for (const Mesh::DrawCall drawCall : skybox.GetDrawCalls())
    {

        // Performs the drawing
        Renderer::DrawSkybox(
                        vertexInputBuffer.data() + drawCall.first,
                        sizeof(Mesh::VertexInput) * drawCall.count,
                        drawCall.count,
                        transform->WorldMatrix(),
                        nullptr
                        /* skybox.GetTexture().get() */
                    );

    }
}

auto Camera::Clone() const -> std::unique_ptr<Component>
{
    return std::make_unique<Camera>(false, skybox, skyboxShader);
}

Matrix4x4 Camera::ViewMatrix() const
{
    auto* transform = GetGameObject()->GetComponent<Transform>();
    return Matrix4x4::Camera(transform->WorldPosition(), transform->WorldRotation(),
        { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f });
}

}
