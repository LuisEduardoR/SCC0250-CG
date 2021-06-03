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

