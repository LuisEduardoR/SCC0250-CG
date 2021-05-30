// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# ifndef OBJECT2D_HPP
# define OBJECT2D_HPP

# include <vector>
# include <memory>

# include "Transform.hpp"
# include "Collider2D.hpp"
# include "Geometry.hpp"

/*
    This file contains the base class to represent 2D objects
*/

class Object2D {

public:

    // Transform of this 2D object
    Transform2D transform;

    // Collider of this 2D object
    CircleCollider2D collider;    

    // Collection of shapes that costitute this 2D object's geometry
    Shape2DCollection geometry;

    Vector2 velocity;

    // Constructors
    Object2D(Transform2D transform, CircleCollider2D collider, Shape2DCollection& geometry) {
        this->transform = transform;
        this->collider = collider;
        this->geometry = geometry;
    }

    bool CheckCollision(const Object2D& other) const;
    bool CheckCollision(const Line& other) const;
};

# endif
