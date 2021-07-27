// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Light.hpp"

# include <algorithm>
# include <memory>

std::vector<Light*> Light::lights{};

Light::Light(Color color) : color(color)
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
