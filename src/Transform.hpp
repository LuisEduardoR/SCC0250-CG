// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# ifndef TRANSFORM2D_HPP
# define TRANSFORM2D_HPP

# include <cmath>

# include "Vector.hpp"
union Matrix4x4;

/*
    This file contains the base class to represent 2D objects
*/

class Transform2D {

public:

    Vector2 position;
    float rotation;
    Vector2 scale;

    // Constructors
    Transform2D(Vector2 position = {}, float rotation = 0.0f, Vector2 scale = { 1.0f, 1.0f });

    // Gets the 4x4 transformation matrix for this object.
    Matrix4x4 GetTransformationMatrix();

};

# endif
