#ifndef HEALTH_BAR_HPP
#define HEALTH_BAR_HPP

#include "Component.hpp"
#include "RendererComponent.hpp"
#include "../Events/Listener.hpp"
#include "../Math/Vector.hpp"

class Health;

class HealthBar : public Adven::Component
{
public:
    HealthBar(Health& health, Vector2 rectMin, Vector2 rectMax);
    ~HealthBar() override = default;
public:
    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    auto Start() -> void override;
private:
    auto HealthChangeHandler(Health& health) -> void;
private:
    RendererComponent<Quad>* renderer;
    Adven::Listener<void(Health&)> healthListener
    {
        [this](Health& health){ return HealthChangeHandler(health); }
    };
    Vector2 rectMin;
    Vector2 rectMax;
};

#endif /* end of include guard: HEALTH_BAR_HPP */
