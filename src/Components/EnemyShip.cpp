// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "EnemyShip.hpp"

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

EnemyShip::EnemyShip(Transform* targetTransform)
    : targetTransform(targetTransform) {} 

auto EnemyShip::Clone() const -> std::unique_ptr<Component>
{
    return std::make_unique<EnemyShip>(targetTransform);
}

void EnemyShip::Start()
{
    transform = GetGameObject()->GetComponent<Transform>();
}

void EnemyShip::VDrawUpdate()
{
    if (!transform)
    {
        std::cout << "EnemyShip expects a Transform\n";
        return;
    }

    if (!targetTransform)
    {
        std::cout << "EnemyShip expects a target Transform\n";
        return;
    }

    Vector2 targetPos = Vector2 { targetTransform->WorldPosition() };

    // Aim ship at target
    Vector2 pos = targetPos - Vector2{ transform->WorldPosition() };
    if (pos.Magnitude() >= 0.005f)
    {
        pos.Normalize();
        float shipAngle = std::atan2(1.0f, 0.0f);
        float aimAngle = std::atan2(pos.y, pos.x);

        transform->localRotation = Vector3{ 0.0f, 0.0f, aimAngle - shipAngle };
    }
}
