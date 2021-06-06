// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Boss.hpp"

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

Boss::Boss(float amplitude, float speed)
    : amplitude(amplitude), speed(speed) {}

auto Boss::Clone() const -> std::unique_ptr<Component>
{
    return std::make_unique<Boss>(amplitude, speed);
}

void Boss::Start()
{
    transform = GetGameObject()->GetComponent<Transform>();
    moveable = GetGameObject()->GetComponent<Moveable>();

    targetPos = transform->localPosition.x + amplitude/2.0f;
    moveable->speed.x = -speed;
    goingRight = true;
}

void Boss::VDrawUpdate()
{
    if (!transform)
    {
        std::cout << "Boss expects a Transform\n";
        return;
    }

    if (!moveable)
    {
        std::cout << "Boss expects a Moveable\n";
        return;
    }

    Scene* currentScene = Scene::currentScene;

    if(goingRight && transform->localPosition.x >= targetPos)
    {
        moveable->speed.x = speed;
        goingRight = false;
        targetPos -= amplitude;
    }
    else if(!goingRight && transform->localPosition.x <= targetPos)
    {
        moveable->speed.x = -speed;
        goingRight = true;
        targetPos += amplitude;
    }
}

void Boss::VBlankUpdate() {}
