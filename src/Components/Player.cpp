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

# include "../Time/Time.hpp"
# include "../Math/Matrix4x4.hpp"
# include "../Input/Input.hpp"
# include "../Rendering/Geometry2D.hpp"
# include "../Scene/Scene.hpp"
# include "../Scene/GameScene.hpp"
# include "../Physics/CircleCollider.hpp"
# include "../Math/Vector.hpp"
# include "../Rendering/Geometry2D.hpp"

# include <iostream>
# include <chrono>
# include <cassert>

using namespace Adven;

Player::Player(std::shared_ptr<GameObject> bulletPrefab) : bulletPrefab(bulletPrefab) {}

auto Player::Clone() const -> std::unique_ptr<Component>
{
    return std::make_unique<Player>(bulletPrefab);
}

void Player::Start()
{
    // Gets the player components
    transform = GetGameObject()->GetComponent<Transform>();
    moveable = GetGameObject()->GetComponent<Moveable>();

    // Initializes lastShotTime to the start of our clock
    // (technically if you played at Thursday, 1 January 1970 00:00:00 GMT 
    // on a UNIX system there's a bug were you would need to wait for the 
    // delay at the start of the game)
    lastShotTime = 0;
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

    // Calculates how much time has passed since last shot
    uint64_t currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    float timeSinceLastShot = (currentTime - lastShotTime) / 1000.0f;

    // Shots if the button is pressed and not currently in the delay time
    if(Input::spacePressed && timeSinceLastShot > shootingDelay)
    {
        GameObject& bullet = currentScene->AddGameObject(GameObject{ *bulletPrefab });

        Vector4 spawnPoint = 
            transform->WorldMatrix()
                * Vector4 { 0.0f, 0.66f + 0.2f, 0.0f, 1.0f };

        Transform* bulletTransform = bullet.GetComponent<Transform>();
        assert(bulletTransform);
        bulletTransform->localPosition = Vector3{ spawnPoint };
        bulletTransform->localRotation = transform->localRotation;
        bulletTransform->localScale = transform->localScale;

        CircleCollider* bulletCollider = bullet.GetComponent<CircleCollider>();
        bulletCollider->radius *= bulletTransform->localScale.x;

        Moveable* bulletRb = bullet.GetComponent<Moveable>();
        assert(bulletRb);
        bulletRb->speed = { 0.0f, 0.5f, 0.0f };

        // Updates last shot time to calculate the new delay
        lastShotTime = currentTime;

    }
}

void Player::VBlankUpdate() {}
