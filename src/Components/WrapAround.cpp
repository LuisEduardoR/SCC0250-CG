#include "WrapAround.hpp"

#include "GameObject.hpp"
#include "Transform.hpp"
#include <memory>

auto WrapAround::Clone() const -> std::unique_ptr<Component>
{
    return std::make_unique<WrapAround>();
}

auto WrapAround::VDrawUpdate() -> void
{
    if (auto* transform = GetGameObject()->GetComponent<Transform>())
    {
        transform->localPosition = Vector3
        {
            std::fmod(transform->localPosition.x + 1.0f, 2.0f) - 1.0f,
            std::fmod(transform->localPosition.y + 1.0f, 2.0f) - 1.0f,
            transform->localPosition.z
        };
    }
}
