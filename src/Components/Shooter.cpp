// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Shooter.hpp"

# include "GameObject.hpp"
# include "Moveable.hpp"
# include "Transform.hpp"

# include "../Time/Time.hpp"
# include "../Math/Matrix4x4.hpp"
# include "../Input/Input.hpp"
# include "../Scene/Scene.hpp"
# include "../Scene/GameScene.hpp"
# include "../Math/Vector.hpp"
# include "../Rendering/Geometry.hpp"
# include "../Physics/CircleCollider.hpp"

# include <iostream>
# include <chrono>
# include <cassert>

using namespace Adven;

Shooter::Shooter(std::shared_ptr<Adven::GameObject> bulletPrefab, Vector3 cannonOffset, float startingDelay, float shootingDelay)
    : bulletPrefab(bulletPrefab), cannonOffset(cannonOffset), active(true), startingDelay(startingDelay), shootingDelay(shootingDelay) {}

auto Shooter::Clone() const -> std::unique_ptr<Component>
{
    return std::make_unique<Shooter>(bulletPrefab, cannonOffset, startingDelay, shootingDelay);
}

void Shooter::Start()
{
    // Gets the Shooter components
    transform = GetGameObject()->GetComponent<Transform>();

    currentTime = startingDelay;
}

void Shooter::VDrawUpdate()
{
    if (!transform)
    {
        std::cout << "Shooter expects a Transform\n";
        return;
    }

    Scene* currentScene = Scene::currentScene;

    // Calculates how much time has passed since last shot
    currentTime += Time::DeltaTime;

    // Shots if the button is pressed and not currently in the delay time
    if(active && currentTime > shootingDelay)
    {
        GameObject& bullet = currentScene->AddGameObject(GameObject{ *bulletPrefab });

        Vector4 spawnPoint = 
            transform->WorldMatrix()
                * Vector4 { cannonOffset, 1.0f };

        Transform* bulletTransform = bullet.GetComponent<Transform>();
        assert(bulletTransform);
        bulletTransform->localPosition = Vector3{ spawnPoint };
        bulletTransform->localRotation = bulletTransform->localRotation + transform->localRotation;
        bulletTransform->localScale = {
            bulletTransform->localScale.x * transform->localScale.x,
            bulletTransform->localScale.y * transform->localScale.y,
            bulletTransform->localScale.z * transform->localScale.z,
        };

        CircleCollider* bulletCollider = bullet.GetComponent<CircleCollider>();
        bulletCollider->radius *= bulletTransform->localScale.x;

        Moveable* bulletPrefabRb = bullet.GetComponent<Moveable>();
        assert(bulletPrefabRb);
        Moveable* bulletRb = bullet.GetComponent<Moveable>();
        assert(bulletRb);

        bulletRb->speed = Vector3 {
            Matrix4x4::Rotate(transform->localRotation)
            * Vector4{ 
                bulletPrefabRb->speed,
                1.0f
            }
        };

        if (afterSpawn)
        {
            afterSpawn(bullet);
        }

        // Sets currentTime back to 0
        currentTime = 0.0f;
    }
}

void Shooter::VBlankUpdate() {}
