// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Player.hpp"

# include "Transform.hpp"
# include "ShapeRenderer.hpp"

# include "../Time/Time.hpp"
# include "../Math/Matrix4x4.hpp"
# include "../Input/Input.hpp"
# include "../Rendering/Geometry2D.hpp"
# include "../Scene/Scene.hpp"
# include "../Scene/GameScene.hpp"
# include "../Physics/CircleCollider.hpp"

# include <iostream>
# include <chrono>

using namespace Adven;

void Player::Start()
{

    // Gets the player components
    transform = gameObject->GetComponent<Transform>();
    moveable = gameObject->GetComponent<Moveable>();

    // Creates a model for our bullet
    bulletModel = Shape2DCollection{ new std::vector<std::unique_ptr<Shape2D>>{} };
    bulletModel->push_back(std::unique_ptr<Line>{ new Line {
        { 0.0f, 0.0f }, { 0.0f, 1.0f }
    }});

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

        GameObject& bullet = currentScene->AddGameObject({});

        Vector4 spawnPoint = 
            transform->WorldMatrix()
                * Vector4 { 0.0f, 0.66f + 0.2f, 0.0f, 1.0f };

        bullet.AddComponent<Transform>(
            Vector3{ spawnPoint },
            Vector3{ transform->localRotation },
            Vector3{ transform->localScale });

        bullet.AddComponent<ShapeRenderer>(bulletModel);
        Moveable& bulletRb = bullet.AddComponent<Moveable>();
        bullet.AddComponent<CircleCollider>( 0.02f, true );

        bulletRb.speed = { 0.0f, 0.5f, 0.0f };

        // Updates last shot time to calculate the new delay
        lastShotTime = currentTime;

    }
}

void Player::VBlankUpdate() {}