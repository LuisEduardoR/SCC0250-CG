// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Player.hpp"

#include "DamageOnContact.hpp"
# include "GameObject.hpp"
# include "Moveable.hpp"
# include "Transform.hpp"
# include "Shooter.hpp"

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
}

void Player::VDrawUpdate()
{
    if (Input::p == Input::State::Down)
        Renderer::ToggleWireframe();

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

    // Updates the X position (based on input)
    if (Input::right == Input::State::Down || Input::right == Input::State::Held)
        input.x = -1.00f;
    else if (Input::left == Input::State::Down || Input::left == Input::State::Held)
        input.x = 1.00f;

    // Updates the Y position (based on input)
    if (Input::space == Input::State::Down || Input::space == Input::State::Held)
        input.y = -1.00f;
    else if (Input::shift == Input::State::Down || Input::shift == Input::State::Held)
        input.y = 1.00f;

    // Updates the Z position (based on input)
    if (Input::up == Input::State::Down || Input::up == Input::State::Held)
        input.z = 1.00f;
    else if (Input::down == Input::State::Down || Input::down == Input::State::Held)
        input.z = -1.00f;

    Vector3 accel { Matrix4x4::Rotate(transform->localRotation) * Vector4{ input } };
    /* moveable->speed = (moveable->speed + accel * Time::DeltaTime).ClampMagnitude(maxSpeed); */ 
    moveable->speed = accel * maxSpeed;

    // Gets the shooters and sets if they're active based on Input
}
