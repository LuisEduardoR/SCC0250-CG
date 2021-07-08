# include "RenderParamInput.hpp"

# include "../Rendering/Renderer.hpp"
# include "../Input/Input.hpp"

auto RenderParamInput::Clone() const -> std::unique_ptr<Component>
{
    return std::make_unique<RenderParamInput>();
}

auto RenderParamInput::VDrawUpdate() -> void
{
    if (Input::p == Input::State::Down)
        Renderer::ToggleWireframe();
}
