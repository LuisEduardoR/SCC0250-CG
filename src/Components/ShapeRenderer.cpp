// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "ShapeRenderer.hpp"

# include "Transform.hpp"
# include "GameObject.hpp"

# include <iostream>


ShapeRenderer::ShapeRenderer(Shape2DCollection geometry)
    : geometry(geometry) {}


auto ShapeRenderer::Clone() const -> std::unique_ptr<Component>
{
    return std::make_unique<ShapeRenderer>(geometry);
}

void ShapeRenderer::VDrawUpdate()
{
    auto* transform = GetGameObject()->GetComponent<Transform>();
    Matrix4x4 world = transform != nullptr ? transform->WorldMatrix()
        : Matrix4x4::Identity;

    Renderer::DrawShape2DCollection(geometry, world);
}
