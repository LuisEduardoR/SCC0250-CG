# include "DamageOnContact.hpp"
# include "Health.hpp"
# include "../Physics/Collider.hpp"

using namespace Adven;

DamageOnContact::DamageOnContact(std::uint32_t damage, bool selfDestruct) : damage(damage), selfDestruct(selfDestruct) {};

auto DamageOnContact::Start() -> void
{
    if (Collider* collider = GetGameObject()->GetComponent<Collider>())
    {
        collider->OnCollision().Subscribe(collisionListener);
    }
}

auto DamageOnContact::Clone() const -> std::unique_ptr<Component>
{
    return std::make_unique<DamageOnContact>(damage);
}

auto DamageOnContact::CollisionHandler(Adven::Collider* myCollider, Adven::Collider* otherCollider) -> void
{
    (void) myCollider; //unused

    if (auto* health = otherCollider->GetGameObject()->GetComponent<Health>())
    {
        (*health) -= damage; 
    }

    if (selfDestruct)
    {
        GetGameObject()->MarkForDestroy();
    }
}
