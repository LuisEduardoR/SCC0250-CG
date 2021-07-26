// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Voidmouth.hpp"

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
# include "../Rendering/Renderer.hpp"

# include <iostream>
# include <chrono>
# include <cassert>

using namespace Adven;

Voidmouth::Voidmouth(std::vector<Vector3> path) : path(path) {}

auto Voidmouth::Clone() const -> std::unique_ptr<Component>
{
    return std::make_unique<Voidmouth>(path);
}

void Voidmouth::Start()
{
    // Gets the Voidmouth components
    transform = &GetGameObject()->RequireComponent<Transform>();
    moveable = &GetGameObject()->RequireComponent<Moveable>();

    // Places Voidmouth at path[0]
    transform->localPosition = path[0];
}

void Voidmouth::VDrawUpdate()
{
    if (transform->localPosition.Magnitude() - path[currentNode].Magnitude() <= 0.1f) // Check if node has been reached (not == because of floating point)
    {
        currentNode = currentNode + 1 < path.size() ? currentNode + 1 : 0;
        moveable->speed = (path[currentNode] - transform->localPosition).Normalized() * maxSpeed;
        Vector4 rotation = { transform->localRotation, 1.0f };
        Matrix4x4 rotationMatrix = Matrix4x4::LookAt(transform->localPosition, path[currentNode], Vector3(0.0f, 1.0f, 0.0f));
        transform->localPosition = (Vector3) (rotationMatrix * rotation);
    }
}
