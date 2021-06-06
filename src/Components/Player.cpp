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
    transform = GetGameObject()->GetComponent<Transform>();
    moveable = GetGameObject()->GetComponent<Moveable>();
    collider = GetGameObject()->GetComponent<CircleCollider>();    
    shooters = GetGameObject()->GetComponents<Shooter>();

    for (Shooter* shooter: shooters)
        shooter->afterSpawn = [this](GameObject& bullet)
        {
            if (auto* damager = bullet.GetComponent<DamageOnContact>())
            {
                damager->damage = damage;
            }
        };

    SetSize(Size::Normal);
}

auto Player::SetSize(Size size) -> void
{
    switch (size)
    {
    case Size::Small:
    {
        transform->localScale = Vector3{ 0.075f, 0.075f, 1.0f };
        maxSpeed = 1.0f;
        damage = 10;
        collider->radius = 0.66f * 0.075f;
    }
    break;
    case Size::Normal:
    {
        transform->localScale = Vector3{ 0.15f, 0.15f, 1.0f };
        maxSpeed = 0.6f;
        damage = 20;
        collider->radius = 0.66f * 0.15f;
    }
    break;
    case Size::Big:
    {
        transform->localScale = Vector3{ 0.3f, 0.3f, 1.0f };
        maxSpeed = 0.3f;
        damage = 30;
        collider->radius = 0.66f * 0.3f;
    }
    break;
    };
    this->size = size;
}

void Player::VDrawUpdate()
{
    if (!transform)
    {
        std::cout << "Player expects a Transform";
        return;
    }

    if (!moveable)
    {
        std::cout << "Player expects a Moveable component";
        return;
    }

    // Updates the scale (based on input)
    if (Input::space == Input::State::Down)
    {
        switch (size)
        {
            case Size::Small:
                SetSize(Size::Normal);
            break;
            case Size::Normal:
                SetSize(Size::Big);
            break;
            default:
            {}
        }
    }
    else if (Input::shift == Input::State::Down)
    {
        switch (size)
        {
            case Size::Normal:
                SetSize(Size::Small);
            break;
            case Size::Big:
                SetSize(Size::Normal);
            break;
            default:
            {}
        }
    }

    // Vector2 targetPos
    // {
    //     (Input::mousePosition.x - WINDOW_WIDTH  / 2.0f) / (WINDOW_WIDTH  / 2.0f),                            
    //     (Input::mousePosition.y - WINDOW_HEIGHT / 2.0f) / (WINDOW_HEIGHT / 2.0f)
    // };

    // Aim ship at cursor
    // Vector2 pos = Vector2{ transform->WorldPosition() } - targetPos;
    // if (pos.Magnitude() >= 0.005f)
    // {
    //     targetPos.Normalize();
    //     float shipAngle = std::atan2(1.0f, 0.0f);
    //     float aimAngle = std::atan2(targetPos.y, targetPos.x);

    //     transform->localRotation = Vector3{ 0.0f, 0.0f, aimAngle - shipAngle };
    // }

    Vector2 input = Vector2();

    // Updates the X position (based on input)
    if (Input::right == Input::State::Down || Input::right == Input::State::Held)
        input.x = 1.00f;
    else if (Input::left == Input::State::Down || Input::left == Input::State::Held)
        input.x = -1.00f;

    // Updates the Y position (based on input)
    if (Input::up == Input::State::Down || Input::up == Input::State::Held)
        input.y = 1.00f;
    else if (Input::down == Input::State::Down || Input::down == Input::State::Held)
        input.y = -1.00f;

    transform->localRotation.z -= input.x * 3.0f * Time::DeltaTime;

    Vector3 accel {
        Matrix4x4::Rotate(transform->localRotation)
        * Vector4{ 
            0.0f,
            input.y,
            0.0f, 1.0f
        }
    };
    moveable->speed = (moveable->speed + accel * Time::DeltaTime).ClampMagnitude(maxSpeed); 


    // moveable->speed = Vector3{ input * maxSpeed };

    // Gets the shooters and sets if they're active based on Input
    for(Shooter* shooter : shooters)
        shooter->active = Input::leftMouse == Input::State::Down || Input::leftMouse == Input::State::Held;
}
