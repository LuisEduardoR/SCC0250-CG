# include "Light.hpp"

# include <algorithm>
#include <memory>

std::vector<Light*> Light::lights{};

Light::Light(Vector3 color) : color(color)
{
    lights.push_back(this);
}

Light::~Light()
{
    auto i = std::find(lights.cbegin(), lights.cend(), this);
    lights.erase(i);
}

auto Light::Clone() const -> std::unique_ptr<Component>
{
    return std::make_unique<Light>(color);
}
