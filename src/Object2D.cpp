// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Object2D.hpp"

bool Object2D::CheckCollision(const Object2D& other) const
{
    float xDistance = transform.position.x - other.transform.position.y;
    float yDistance = transform.position.y - other.transform.position.y;

    return collider.radius * collider.radius + other.collider.radius * other.collider.radius
        >= xDistance * xDistance + yDistance * yDistance;
}

bool Object2D::CheckCollision(const Line& other) const
{
    //dot(a - b);
    return true;
}
