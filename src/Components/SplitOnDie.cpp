# include "SplitOnDie.hpp"

# include <memory>
# include <random>

# include "GameObject.hpp"
# include "Health.hpp"
# include "Transform.hpp"
# include "Moveable.hpp"
# include "../Physics/CircleCollider.hpp"
# include "../Rendering/Geometry.hpp"
# include "../Scene/Scene.hpp"

using namespace Adven;

SplitOnDie::SplitOnDie(std::shared_ptr<GameObject> prefab) : prefab(prefab) {}

auto SplitOnDie::Start() -> void
{
    if (Health* health = GetGameObject()->GetComponent<Health>())
    {
        health->OnDie().Subscribe(deathListener);
    }
}

[[nodiscard]] auto SplitOnDie::Clone() const -> std::unique_ptr<Component>
{
    return std::make_unique<SplitOnDie>(prefab);
}

auto SplitOnDie::DeathHandler(Health&) -> void
{
    auto* myTransform = GetGameObject()->GetComponent<Transform>();
    Vector3 myPosition = myTransform ? myTransform->WorldPosition() : Vector3{};

	std::random_device rd;
	std::mt19937 rng{ rd() };

    std::uniform_real_distribution<float> posDistribution{ -0.1f, 0.1f };
    std::uniform_real_distribution<float> angleDistribution{ 0.0f, 1.0f };
    std::uniform_real_distribution<float> scaleDistribution{ 0.02f, 0.06f };
    std::uniform_real_distribution<float> speedDistribution{ -0.1f, 0.1f };

    int count = std::uniform_int_distribution<int>{ 1, 4 }(rng);
    
    for (int i = 0; i < count; i++)
    {
        GameObject& spawn = GetGameObject()->GetScene()->AddGameObject(GameObject{ *prefab });
        const float scale = scaleDistribution(rng);

        if (auto* transform = spawn.GetComponent<Transform>())
        {
            transform->localPosition = myPosition + Vector3
            {
                posDistribution(rng),
                posDistribution(rng),
                0.0f,
            };
            transform->localRotation = { 0.0f, 0.0f, 2.0f * CONST_PI * angleDistribution(rng) };
            transform->localScale = { scale, scale, 1.0f };
        }

        if (auto* moveable = spawn.GetComponent<Moveable>())
        {
            moveable->speed = Vector3
            {
                speedDistribution(rng),
                speedDistribution(rng),
                0.0f,
            };
        }

        if (auto* collider = spawn.GetComponent<CircleCollider>())
        {
            collider->radius = scale;
        }
    }
}
