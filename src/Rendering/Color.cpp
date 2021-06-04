// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Color.hpp"

# include <random>
# include <cmath>

// Constructors
Color::Color(float r, float g, float b, float a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Color::Color(int r, int g, int b, int a) {
    this->r = r / 255.0f;
    this->g = g / 255.0f;
    this->b = b / 255.0f;
    this->a = a / 255.0f;
}

// Some default colors constants:
const Color Color::black    = { 0.0f, 0.0f, 0.0f };
const Color Color::white    = { 1.0f, 1.0f, 1.0f };
const Color Color::grey     = { 0.5f, 0.5f, 0.5f };
const Color Color::red      = { 1.0f, 0.0f, 0.0f };
const Color Color::green    = { 0.0f, 1.0f, 0.0f };
const Color Color::blue     = { 0.0f, 0.0f, 1.0f };
const Color Color::cyan     = { 0.0f, 1.0f, 1.0f };
const Color Color::magenta  = { 1.0f, 0.0f, 1.0f };
const Color Color::yellow   = { 1.0f, 1.0f, 0.0f };

// Returns a random color (but always with alpha set to 1.0f)
Color Color::random(unsigned seed) {
    std::mt19937 rng{};
    return Color(   
                    std::uniform_real_distribution<float>{ 0.0f, 1.0f }(rng), 
                    std::uniform_real_distribution<float>{ 0.0f, 1.0f }(rng), 
                    std::uniform_real_distribution<float>{ 0.0f, 1.0f }(rng), 
                    1.0f
                );
}

// Compares colors by converting their components to int to avoid float precision errors
auto operator==(const Color& a, const Color& b) -> bool
{
    return  static_cast<int32_t>(roundf(a.r * 255.0f)) == static_cast<int32_t>(roundf(b.r * 255.0f))
            && static_cast<int32_t>(roundf(a.g * 255.0f)) == static_cast<int32_t>(roundf(b.g * 255.0f))
            && static_cast<int32_t>(roundf(a.b * 255.0f)) == static_cast<int32_t>(roundf(b.b * 255.0f))
            && static_cast<int32_t>(roundf(a.a * 255.0f)) == static_cast<int32_t>(roundf(b.a * 255.0f));
}
