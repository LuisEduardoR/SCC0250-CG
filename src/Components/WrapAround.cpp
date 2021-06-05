#include "WrapAround.hpp"

#include "GameObject.hpp"
#include "Transform.hpp"
#include <memory>

namespace
{
    float Mod(float a, float b)
    {
        return std::signbit(a) ? std::fmod(a + 1.0f, b) + b - 1.0f : std::fmod(a, b);
    }
}

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
            Mod(transform->localPosition.x + 1.0f, 2.0f) - 1.0f,
            Mod(transform->localPosition.y + 1.0f, 2.0f) - 1.0f,
            transform->localPosition.z
        };
    }
}
