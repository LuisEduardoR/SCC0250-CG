// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the PlayerDeath component
    Implements a death mechanic for when the health
    of a GameObject with Player and Health components
    runs out
*/

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
