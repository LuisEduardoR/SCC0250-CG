#include "TimedSpawner.hpp"

#include <memory>

#include "GameObject.hpp"
#include "../Scene/Scene.hpp"
#include "../Time/Time.hpp"
#include "Player.hpp"

using namespace Adven;

TimedSpawner::TimedSpawner(std::shared_ptr<GameObject> prefab, float timeToSpawn)
    : prefab(prefab), timeToSpawn(timeToSpawn) {}


[[nodiscard]] auto TimedSpawner::Clone() const -> std::unique_ptr<Component>
{
    return std::make_unique<TimedSpawner>(prefab, timeToSpawn);
}

auto TimedSpawner::Start() -> void
{
    startTime = Time::Time;
}

auto TimedSpawner::VDrawUpdate() -> void
{
    if (Time::Time >= startTime + timeToSpawn)
    {
        if (Scene* scene = GetGameObject()->GetScene())
        {
            scene->AddGameObject(GameObject{ *prefab });
        }
        GetGameObject()->MarkForDestroy();
    }
}
