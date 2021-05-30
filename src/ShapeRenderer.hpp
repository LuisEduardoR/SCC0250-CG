// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

#include <memory>

#include "adven/Component.hpp"
#include "Geometry.hpp"
#include "Renderer.hpp"

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