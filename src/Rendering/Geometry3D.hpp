// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the base classes to represent 3D geometry
*/

# ifndef GEOMETRY3D_HPP
# define GEOMETRY3D_HPP

# include "../Math/Vector.hpp"

# include <vector>

// Represents a triangle in 3D space
class Triangle3D {

public:

    Vector3 a, b, c;

    // Constructors
    Triangle3D(Vector3 a, Vector3 b, Vector3 c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }
    Triangle3D() : Triangle3D({ 0.0f, 0.5f, 0.0f}, { -0.5f, -0.5f, 0.0f}, { 0.5f, -0.5f, 0.0f}) {}    

};

// Represents a generic 3D mesh composed by triangles
class Mesh3D {

private:

    std::vector<Triangle3D> triangles;

public:  

    // Constructors
    Mesh3D(std::vector<Triangle3D> triangles) {
        this->triangles = triangles;
    }

    // Returns the triangles of our mesh
    std::vector<Triangle3D> GetTriangles() const;

};

# endif /* end of include guard: GEOMETRY3D_HPP */
