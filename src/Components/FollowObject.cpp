// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

#include "FollowObject.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"

FollowObject::FollowObject(Transform* follow, Vector3 offset)
    : follow(follow), offset(offset) {}

auto FollowObject::Clone() const -> std::unique_ptr<Component>
{
    return std::make_unique<FollowObject>(follow, offset);
}

auto FollowObject::VDrawUpdate() -> void
{
    if (auto* transform = GetGameObject()->GetComponent<Transform>())
    {
        transform->localPosition = follow->WorldPosition() + offset;
    }
}

