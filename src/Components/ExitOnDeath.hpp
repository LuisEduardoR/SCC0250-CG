#ifndef EXIT_ON_DEATH_HPP
#define EXIT_ON_DEATH_HPP

#include <string>

#include "Component.hpp"
#include "../Events/Listener.hpp"

class Health;

class ExitOnDeath : public Adven::Component
{
public:
    ExitOnDeath(std::string&& message);
    ~ExitOnDeath() override = default;

public:
    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    auto Start() -> void override;
private:
    auto DeathHandler(Health& health) -> void;

    Adven::Listener<void(Health&)> deathListener
    {
        [this](Health& health){ DeathHandler(health); }
    };

    std::string message;
};

#endif /* end of include guard: EXIT_ON_DEATH_HPP */
