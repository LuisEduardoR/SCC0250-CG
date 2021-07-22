// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the RendererComponent component
    Implements a way call the renderer to draw something
    ons screen for the GameObject with this component
*/

# ifndef COMPONENT_RENDERER_HPP
# define COMPONENT_RENDERER_HPP

#include <memory>

# include "Component.hpp"

# include "Transform.hpp"
# include "GameObject.hpp"

# include "../Rendering/Renderer.hpp"

template<class T>
class RendererComponent : public Adven::Component {

public:

    T data;

    RendererComponent(T data) : data(data) {}
    ~RendererComponent() override = default;

    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> {
        return std::make_unique<RendererComponent>(data);
    }
    void VDrawUpdate() override {

        auto* transform = GetGameObject()->GetComponent<Transform>();
        Matrix4x4 world = transform != nullptr ? transform->WorldMatrix()
            : Matrix4x4::Identity;

        Renderer::Draw<T>(data, world);

    }
};

# endif /* end of include guard: COMPONENT_RENDERER_HPP */
