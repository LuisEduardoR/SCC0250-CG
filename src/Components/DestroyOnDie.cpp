# include "DestroyOnDie.hpp"

# include <memory>

# include "GameObject.hpp"
# include "Health.hpp"

auto DestroyOnDie::DeathHandler(Health& health) -> void
{
    health.GetGameObject()->MarkForDestroy();
}

auto DestroyOnDie::Start() -> void
{
    if (Health* health = GetGameObject()->GetComponent<Health>())
    {
        health->OnDie().Subscribe(deathListener);
    }
}

[[nodiscard]] auto DestroyOnDie::Clone() const -> std::unique_ptr<Component>
{
    return std::make_unique<DestroyOnDie>();
}
