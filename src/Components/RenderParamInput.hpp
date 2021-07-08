# ifndef RENDER_PARAM_INPUT_HPP
# define RENDER_PARAM_INPUT_HPP

# include "Component.hpp"

class RenderParamInput : public Adven::Component
{
public:
    RenderParamInput() = default;
public:
    ~RenderParamInput() override = default;
public:
    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    auto VDrawUpdate() -> void override;
};

# endif /* end of include guard: RENDER_PARAM_INPUT_HPP */
