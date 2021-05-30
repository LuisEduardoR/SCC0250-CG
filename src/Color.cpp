// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Color.hpp"

// Constructors
Color::Color(float r, float g, float b, float a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Color::Color(int r, int g, int b, int a) {
    this->r = r/255.0f;
    this->g = g/255.0f;
    this->b = b/255.0f;
    this->a = a/255.0f;
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
    std::minstd_rand rng(seed);
    return Color(   
                    (float)rng() / 2147483646.0f, 
                    (float)rng() / 2147483646.0f, 
                    (float)rng() / 2147483646.0f, 
                    1.0f
                );
}
