#include "PlayerDeath.hpp"

#include <iostream>
#include <memory>

#include "GameObject.hpp"
#include "Health.hpp"
#include "../Events/Event.hpp"

auto PlayerDeath::Clone() const -> std::unique_ptr<Component>
{
    return std::make_unique<PlayerDeath>(); 
}

auto PlayerDeath::Start() -> void
{
    if (auto* health = GetGameObject()->GetComponent<Health>())
    {
        health->OnDie().Subscribe(deathListener);
    }
}

auto PlayerDeath::DeathHandler(Health&) -> void
{
    std::cout << "GAMEOVER!\nYou died!\n\n";
    std::exit(0);
}
