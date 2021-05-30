// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Player.hpp"
# include "Transform.hpp"
# include "Time.hpp"
# include "Matrix4x4.hpp"
# include <iostream>
# include "Input.hpp"
# include "adven/Scene.hpp"
# include "Geometry.hpp"
# include "TestScene.hpp"
# include "adven/CircleCollider.hpp"
# include "ShapeRenderer.hpp"

using namespace Adven;

void Player::Start()
{
    transform = gameObject->GetComponent<Transform>();
    moveable = gameObject->GetComponent<Moveable>();

    bulletModel = Shape2DCollection{ new std::vector<std::unique_ptr<Shape2D>>{} };
    bulletModel->push_back(std::unique_ptr<Line>{ new Line {
        { 0.0f, 0.0f }, { 0.0f, 1.0f }
    }});
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

    if(Input::spacePressed)
    {
        GameObject& bullet = currentScene->AddGameObject({});

        Vector4 spawnPoint = 
            transform->WorldMatrix()
                * Vector4 { 0.0f, 0.66f + 0.4f, 0.0f, 1.0f };

        bullet.AddComponent<Transform>(
            Vector3{ spawnPoint },
            Vector3{ transform->localRotation },
            Vector3{ transform->localScale });

        bullet.AddComponent<ShapeRenderer>(bulletModel);
        Moveable& bulletRb = bullet.AddComponent<Moveable>();
        bullet.AddComponent<CircleCollider>( 0.02f, true );

        bulletRb.speed = { 0.0f, 0.5f, 0.0f };
    }
}

void Player::VBlankUpdate() {}