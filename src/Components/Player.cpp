// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Player.hpp"

# include "GameObject.hpp"
# include "Moveable.hpp"
# include "ShapeRenderer.hpp"
# include "Transform.hpp"
# include "Shooter.hpp"

# include "../Time/Time.hpp"
# include "../Math/Matrix4x4.hpp"
# include "../Input/Input.hpp"
# include "../Rendering/Geometry2D.hpp"
# include "../Scene/Scene.hpp"
# include "../Scene/GameScene.hpp"
# include "../Physics/CircleCollider.hpp"
# include "../Math/Vector.hpp"
# include "../Rendering/Geometry2D.hpp"
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
    if(Input::leftMousePressed)
        transform->localScale += 0.50f * Time::DeltaTime;
    else if(Input::rightMousePressed)
        transform->localScale -= 0.50f * Time::DeltaTime;

    GetGameObject()->GetComponent<CircleCollider>()->radius *= transform->localScale.x;

    Vector2 targetPos   {
                            (Input::mousePosition.x - WINDOW_WIDTH  / 2.0f) / (WINDOW_WIDTH  / 2.0f),                            
                            (Input::mousePosition.y - WINDOW_HEIGHT / 2.0f) / (WINDOW_HEIGHT / 2.0f)
                        };

    // Aim ship at cursor
    Vector2 pos =  Vector2{ transform->WorldPosition() } - targetPos;
    Vector2 aimDirection = (Vector2{ transform->WorldPosition() } - targetPos).Normalized();
    float aimAngle = std::atan2(aimDirection.y, aimDirection.x) + (CONST_PI / 2.0f);
    transform->localRotation = Vector3{ 0.0f, 0.0f, aimAngle };

    Vector2 input = Vector2();
    float speed = 1.00f;

    // Updates the X position (based on input)
    if(Input::rightPressed)
        input.x = 1.00f;
    else if(Input::leftPressed)
        input.x = -1.00f;

    // Updates the Y position (based on input)
    if(Input::upPressed)
        input.y = 1.00f;
    else if(Input::downPressed)
        input.y = -1.00f;

    Vector2 velocity = input * speed;
    moveable->speed = Vector3{ velocity };

    Scene* currentScene = Scene::currentScene;

    // Gets the shooters and sets if they're active based on Input
    std::vector<Shooter*> shooters = GetGameObject()->GetComponents<Shooter>();
    for(Shooter* shooter : shooters)
        shooter->active = Input::spacePressed;

}

void Player::VBlankUpdate() {}
