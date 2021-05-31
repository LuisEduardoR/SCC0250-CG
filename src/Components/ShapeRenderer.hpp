// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the ShapeRender component
*/

# ifndef SHAPE_RENDERER_HPP
# define SHAPE_RENDERER_HPP

# include "Component.hpp"

# include "../Rendering/Renderer.hpp"
# include "../Rendering/Geometry2D.hpp"

class ShapeRenderer : public Adven::Component
{
public:
    Shape2DCollection geometry;
public:
    ShapeRenderer(Shape2DCollection geometry);
    ~ShapeRenderer() override = default;
public:
    void VDrawUpdate() override;
};

# endif /* end of include guard: SHAPE_RENDERER_HPP */