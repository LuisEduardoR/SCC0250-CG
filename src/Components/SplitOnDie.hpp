// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the SplitOnDie component
    Causes a Gameobject to split into multiple pieces
    when the health from it's Health component runs out
*/

#ifndef SPLIT_ON_DIE_HPP
#define SPLIT_ON_DIE_HPP

# include "Component.hpp"
# include "../Events/Listener.hpp"

namespace Adven
{
class GameObject;
}

class Health;

class SplitOnDie : public Adven::Component
{
public:
    SplitOnDie(std::shared_ptr<Adven::GameObject> prefab);
    ~SplitOnDie() override = default;
public:
    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    auto Start() -> void override;
private:
    auto DeathHandler(Health& health) -> void;
public:
    std::shared_ptr<Adven::GameObject> prefab;
    Adven::Listener<void(Health&)> deathListener
    {
        [this](Health& health){ return DeathHandler(health); }
    };
};

#endif /* end of include guard: SPLIT_ON_DIE_HPP */
