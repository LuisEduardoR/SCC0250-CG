// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the DestroyOnDie component
    Destroy the GameObject with this component and
    a Health component if it has no more health
*/

# ifndef DESTROY_ON_DIE_HPP
# define DESTROY_ON_DIE_HPP

# include "Component.hpp"
# include "../Events/Listener.hpp"

class Health;

class DestroyOnDie : public Adven::Component
{
private:
    static auto DeathHandler(Health& health) -> void;
public:
    ~DestroyOnDie() override = default;
public:
    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    auto Start() -> void override;
public:
    Adven::Listener<void(Health&)> deathListener{ DestroyOnDie::DeathHandler };
};

# endif /* end of include guard: DESTROY_ON_DIE_HPP */
