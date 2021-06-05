#ifndef PLAYER_DEATH_HPP
#define PLAYER_DEATH_HPP

#include "Component.hpp"
#include "../Events/Listener.hpp"

class Health;

class PlayerDeath : public Adven::Component
{
public:
    ~PlayerDeath() override = default;

public:
    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    auto Start() -> void override;
private:
    auto DeathHandler(Health& health) -> void;

    Adven::Listener<void(Health&)> deathListener
    {
        [this](Health& health){ DeathHandler(health); }
    };
};

#endif /* end of include guard: PLAYER_DEATH_HPP */
