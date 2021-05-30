// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# ifndef COLOR_HPP
# define COLOR_HPP

# include <random>

/*
    This file contains the base class to represent colors
*/

class Color {

public:

    float r, g, b, a;

    // Constructors
    Color(float r, float g, float b, float a);
    Color(float r, float g, float b) : Color(r, g, b, 1.0f) {}
    Color(int r, int g, int b, int a);
    Color(int r, int g, int b) : Color(r, g, b, 255) {}
    Color() : Color(0.0f, 0.0f, 0.0f, 0.0f) {}

    // Some default colors constants:
    const static Color black;
    const static Color white;
    const static Color grey;
    const static Color red;
    const static Color green;
    const static Color blue;
    const static Color cyan;
    const static Color magenta;
    const static Color yellow;

    // Returns a random color (but always with alpha set to 1.0f)
    static Color random(unsigned seed);

};

# endif