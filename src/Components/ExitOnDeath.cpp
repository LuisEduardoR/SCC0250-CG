#include "ExitOnDeath.hpp"

#include <iostream>
#include <memory>

#include "GameObject.hpp"
#include "Health.hpp"
#include "../Events/Event.hpp"

ExitOnDeath::ExitOnDeath(std::string&& message) : message(message) {};

auto ExitOnDeath::Clone() const -> std::unique_ptr<Component>
{
    return std::make_unique<ExitOnDeath>(std::string{ message }); 
}

auto ExitOnDeath::Start() -> void
{
    if (auto* health = GetGameObject()->GetComponent<Health>())
    {
        health->OnDie().Subscribe(deathListener);
    }
}

auto ExitOnDeath::DeathHandler(Health&) -> void
{
    std::cout << message << '\n';
    std::exit(0);
}
