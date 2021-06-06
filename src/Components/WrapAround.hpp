// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the WrapAround component
    Causes an object to wrap around if ever going
    outside of the view area
*/

#ifndef WRAP_AROUND_HPP
#define WRAP_AROUND_HPP

#include "Component.hpp"
#include "Player.hpp"
#include <memory>

class WrapAround : public Adven::Component
{
public:
    ~WrapAround() override = default;
public:
    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    auto VDrawUpdate() -> void override;
};

#endif /* end of include guard: WRAP_AROUND_HPP */
