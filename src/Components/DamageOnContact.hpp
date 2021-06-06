# ifndef DAMAGE_ON_CONTACT_HPP
# define DAMAGE_ON_CONTACT_HPP

# include <cstdint>

# include "Component.hpp"
# include "../Events/Listener.hpp"
# include "../Physics/Collider.hpp"

class DamageOnContact : public Adven::Component
{
public:
    DamageOnContact(std::uint32_t damage, bool selfDestruct = true);
    ~DamageOnContact() override = default;
public:
    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    auto Start() -> void override;
private:
    auto CollisionHandler(Adven::Collider* myCollider, Adven::Collider* otherCollider) -> void;
private:
    Adven::Listener<void(Adven::Collider*, Adven::Collider*)> collisionListener
    {
        [this](Adven::Collider* a, Adven::Collider* b)
        {
            CollisionHandler(a, b);
        }
    };
public:
    std::uint32_t damage;
    bool selfDestruct;
};

# endif /* end of include guard: DAMAGE_ON_CONTACT_HPP */
