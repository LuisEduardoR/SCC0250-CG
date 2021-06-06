#ifndef TIMED_SPAWNER_HPP
#define TIMED_SPAWNER_HPP

# include "Component.hpp"

namespace Adven
{
class GameObject;
}

class TimedSpawner : public Adven::Component
{
public:
    TimedSpawner(std::shared_ptr<Adven::GameObject> prefab, float timeToSpawn);
    ~TimedSpawner() override = default;
public:
    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    auto Start() -> void override;
    auto VDrawUpdate() -> void override;
public:
    std::shared_ptr<Adven::GameObject> prefab;
    float timeToSpawn;
    float startTime;
};

#endif /* end of include guard: TIMED_SPAWNER_HPP */
