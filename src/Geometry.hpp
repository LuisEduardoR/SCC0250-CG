// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# ifndef GEOMETRY_HPP
# define GEOMETRY_HPP

# define CONST_PI 3.14159265358979323846

# include <cmath>
# include <vector>

/*
    This file contains the base classes to represent some really simple geometric figures
*/

// Represents a 2D vector, but can also be used to represent 2D coordinates 
class Vector2 {

public:

    float x, y;

    // Constructors
    Vector2(float x, float y);
    Vector2() : Vector2(0.0f, 0.0f) {}

};

// Represents a 3D vector, but can also be used to represent 3D coordinates 
class Vector3 {

public:

    float x, y, z;

    // Constructors
    Vector3(float x, float y, float z);
    Vector3() : Vector3(0.0f, 0.0f, 0.0f) {}

};

// Represents a 4D vector, but can also be used to represent 4D coordinates 
class Vector4 {

public:

    float x, y, z, w;

    // Constructors
    Vector4(float x, float y, float z, float w);
    Vector4() : Vector4(0.0f, 0.0f, 0.0f, 0.0f) {}

};

// Represents a 4D transformation matrix
class Matrix4 {

public:

    Vector4 i, j, k, l;

    // Constructors
    Matrix4(Vector4 i, Vector4 j, Vector4 k, Vector4 l);
    Matrix4() : Matrix4 (
                            Vector4(1.0f, 0.0f, 0.0f, 0.0f), 
                            Vector4(0.0f, 1.0f, 0.0f, 0.0f), 
                            Vector4(0.0f, 0.0f, 1.0f, 0.0f), 
                            Vector4(0.0f, 0.0f, 0.0f, 1.0f)
                        ) {}

    // Operators
    Matrix4 operator*(const Matrix4& m);

};

// Represents a line between 2 points in 2D space
class Line {

public:

    Vector2 a, b;

    // Constructors
    Line(Vector2 a, Vector2 b);
    Line() : Line(Vector2(0.0f, -0.5f), Vector2(0.0f, 0.5f)) {}

};

// Represents a line composed by connecting multiple points in 2D space
class Polyline {

public:

    std::vector<Vector2> points;

    // Constructors
    Polyline();
    Polyline(Vector2 a, Vector2 b);
    Polyline(std::vector<Vector2> points);

};

// Represents a triangle in 2D space
class Triangle {

public:

    Vector2 a, b, c;

    // Constructors
    Triangle(Vector2 a, Vector2 b, Vector2 c);
    Triangle() : Triangle(Vector2(0.0f, 0.5f), Vector2(-0.5f, -0.5f), Vector2(0.5f, -0.5f)) {}    

};

// Represents any shape with 4 sides in 2D space
class Quad {

public:

    Vector2 a, b, c, d;

    // Constructors
    Quad(Vector2 a, Vector2 b, Vector2 c, Vector2 d);
    Quad() : Quad(Vector2(0.5f, 0.5f), Vector2(-0.5f, 0.5f), Vector2(-0.5f, -0.5f), Vector2(0.5f, -0.5f)) {}

};

// Represents a circle in 2D space
class Circle {

public:

    // Precision used to represent the circle when we need to convert it to 2D points
    int precision;
    
    // Default value for precision
    const static int default_precision = 32;

    Vector2 center;

    float radius;    

    // Constructors
    Circle(Vector2 center, float radius, int precision);
    Circle(Vector2 center, float radius) : Circle(center, radius, this->default_precision) {} 
    Circle() : Circle(Vector2(0.0f, 0.0f), 1.0f, this->default_precision) {}

    // Returns a approximation of the circle represented by a vector with a certain number of points
    std::vector<Vector2> GetPoints() const;

};

// Represents a triangle in 3D space
class Triangle3D {

public:

    Vector3 a, b, c;

    // Constructors
    Triangle3D(Vector3 a, Vector3 b, Vector3 c);
    Triangle3D() : Triangle3D(Vector3(0.0f, 0.5f, 0.0f), Vector3(-0.5f, -0.5f, 0.0f), Vector3(0.5f, -0.5f, 0.0f)) {}    

};

// Represents a generic 3D mesh composed by triangles
class Mesh3D {

private:

    std::vector<Triangle3D> triangles;

public:  

    // Constructors
    Mesh3D(std::vector<Triangle3D> triangles);

    // Returns the triangles of our mesh
    std::vector<Triangle3D> GetTriangles() const;

};

# endif