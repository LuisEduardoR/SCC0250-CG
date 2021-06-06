// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the DestroyArea component
    Destroy the GameObject with this component
    if it ever leaves the area
*/

#ifndef DESTROY_AREA_HPP
#define DESTROY_AREA_HPP

#include "Component.hpp"
#include "../Math/Vector.hpp"

class DestroyArea : public Adven::Component
{
public:
    DestroyArea(Vector3 min, Vector3 max);
    ~DestroyArea() override = default;

public:
    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    auto VDrawUpdate() -> void override;
    
public:
    Vector3 min;
    Vector3 max;
};

#endif /* end of include guard: DESTROY_AREA_HPP */
