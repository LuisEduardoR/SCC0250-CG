// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Object2D.hpp"

# include <cmath>

bool Object2D::CheckCollision(const Object2D& other) const
{
    Vector2 distance = transform.position - other.transform.position;

    return std::pow(collider.radius + other.collider.radius, 2)
        >= std::pow(distance.x, 2) + std::pow(distance.y, 2);
}

bool Object2D::CheckCollision(const Line& other) const
{

    //dot(a - b);
    return true;
}
