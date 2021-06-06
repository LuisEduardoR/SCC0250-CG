
// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the DamageOnContact component
    Does damage when a GameObject with a Collider and a 
    Health component collides against this a GameObject 
    with this component and also a Collider
*/

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
    std::uint32_t damage;
    bool selfDestruct;
};

# endif /* end of include guard: DAMAGE_ON_CONTACT_HPP */
