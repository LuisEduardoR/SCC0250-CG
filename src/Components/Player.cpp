// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Player.hpp"

# include "GameObject.hpp"
# include "Moveable.hpp"
# include "Transform.hpp"
# include "Camera.hpp"

# include "../Time/Time.hpp"
# include "../Math/Matrix4x4.hpp"
# include "../Input/Input.hpp"
# include "../Scene/Scene.hpp"
# include "../Scene/GameScene.hpp"
# include "../Physics/CircleCollider.hpp"
# include "../Math/Vector.hpp"
# include "../Rendering/Geometry.hpp"
# include "../Rendering/Renderer.hpp"
# include "../WindowSystem/WindowSystem.hpp"

# include <iostream>
# include <chrono>
# include <cassert>

using namespace Adven;

auto Player::Clone() const -> std::unique_ptr<Component>
{
    return std::make_unique<Player>();
}

void Player::Start()
{
    // Gets the player components
    transform = &GetGameObject()->RequireComponent<Transform>();
    moveable = &GetGameObject()->RequireComponent<Moveable>();
    /* collider = &GetGameObject()->RequireComponent<CircleCollider>(); */    
    WindowSystem::SetCursorMode(WindowSystem::CursorMode::Disabled);
    fov = 2.0f;
}

void Player::VDrawUpdate()
{
    
    auto camera = Camera::MainCamera();

    // Increases ambient light intensity.
    if (Input::u == Input::State::Down || Input::u == Input::State::Held)
        camera->IncreaseAmbientLightIntensity();

    // Decreases ambient light intensity.
    if (Input::p == Input::State::Down || Input::p == Input::State::Held)
        camera->DecreaseAmbientLightIntensity();

    // Toggle wireframe rendering
    if (Input::o == Input::State::Down)
        Renderer::ToggleWireframe();

    // Locks and unlocks the cursor
    if (Input::esc == Input::State::Down)
        WindowSystem::SetCursorMode(WindowSystem::CursorMode::Normal);
    else if (Input::leftMouse == Input::State::Down)
        WindowSystem::SetCursorMode(WindowSystem::CursorMode::Disabled);


    transform->localRotation = { 
        Input::mousePosition.y / 500.f,
        -Input::mousePosition.x / 500.f,
        0.0f,
    };

    Vector3 input{};
    float fovInput = 0.0f;

    // Updates the X position (based on input)
    if (Input::right == Input::State::Down || Input::right == Input::State::Held)
        input.x = 1.00f;
    else if (Input::left == Input::State::Down || Input::left == Input::State::Held)
        input.x = -1.00f;

    // Updates the Z position (based on input)
    if (Input::up == Input::State::Down || Input::up == Input::State::Held)
        input.z = -1.00f;
    else if (Input::down == Input::State::Down || Input::down == Input::State::Held)
        input.z = 1.00f;

    // Updates the Fov (based on input)
    if (Input::rightArrow == Input::State::Down)
        fovInput = 0.25f;
    else if (Input::leftArrow == Input::State::Down)
        fovInput = -0.25f;

    fov += fovInput;
    if (fov < 1.25f)
        fov = 1.25f;

    Vector3 direction { Matrix4x4::Rotate(transform->localRotation) * Vector4{ input, 1.0f } };
    Vector3 posIntent = transform->localPosition + direction.Normalized() * Time::DeltaTime * maxSpeed;
    posIntent.Clamp(lowerBounds, higherBounds);
    transform->localPosition = posIntent;

    // Applies the projection matrix.
    Renderer::SetProjectionMatrix(Matrix4x4::Perspective(CONST_PI / fov, ASPECT, 0.1f, 100.0f));

}
