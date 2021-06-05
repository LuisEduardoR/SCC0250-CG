#include "HealthBar.hpp"

#include <memory>

#include "Health.hpp"
#include "../Exceptions/Exceptions.hpp"
#include "RendererComponent.hpp"

HealthBar::HealthBar(Health& health, Vector2 rectMin, Vector2 rectMax)
    : rectMin(rectMin), rectMax(rectMax)
{
    health.OnChange().Subscribe(healthListener);
}

auto HealthBar::Clone() const -> std::unique_ptr<Component>
{
    // Need cloneable listeners.
    throw Adven::NotImplementedException();
}

auto HealthBar::Start() -> void
{
    renderer = GetGameObject()->GetComponent<RendererComponent<Quad>>();
    renderer->data.a = { rectMin.x, rectMax.y };
    renderer->data.b = rectMin;
    renderer->data.c = rectMax;
    renderer->data.d = { rectMax.x, rectMin.y };
}

auto HealthBar::HealthChangeHandler(Health& health) -> void
{
    const float hpPercent = static_cast<float>(health.Value()) / static_cast<float>(health.MaxValue());
    const Vector2 rectCur = rectMax * hpPercent;

    renderer->data.a = { rectMin.x, rectCur.y };
    renderer->data.b = rectMin;
    renderer->data.c = rectCur;
    renderer->data.d = { rectCur.x, rectMin.y };
}
