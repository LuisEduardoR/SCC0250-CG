#include "DestroyArea.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include <memory>

DestroyArea::DestroyArea(Vector3 min, Vector3 max)
    : min(min), max(max) {}

auto DestroyArea::Clone() const -> std::unique_ptr<Component>
{
    return std::make_unique<DestroyArea>(min, max);
}

auto DestroyArea::VDrawUpdate() -> void
{
    if (auto* transform = GetGameObject()->GetComponent<Transform>())
    {
        Vector3 pos = transform->WorldPosition();

        if (!(pos.x >= min.x && pos.x <= max.x &&
            pos.y >= min.y && pos.y <= max.y &&
            pos.z >= min.z && pos.z <= max.z))
        {
            GetGameObject()->MarkForDestroy(); 
        }
    }
}

