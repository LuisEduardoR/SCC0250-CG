// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# ifndef GEOMETRY_HPP
# define GEOMETRY_HPP

# define CONST_PI 3.14159265358979323846

# include <GL/glew.h>
# include <cmath>
# include <vector>
# include <memory>

# include "Color.hpp"

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

class Shape2D {

public:

    Color color;

    // Constructors
    Shape2D(Color color) {
        this->color = color;
    }
    Shape2D() : Shape2D(Color::white) {}

    // Destructors
    virtual ~Shape2D() = default;

    // Returns the vertices used to represent this shape
    virtual std::vector<Vector2> GetVertices() const = 0;

    // Returns the draw mode of this shape
    virtual GLenum GetDrawMode() const = 0;

};

// Represents a point in 2D space
class Point :  public Shape2D {

public:

    Vector2 a;

    // Constructors
    Point(Vector2 a, Color color = Color::white) : Shape2D(color) {
        this->a = a;
    }
    Point() : Point(Vector2()) {}

    // Destructors
    virtual ~Point() = default;

    // Returns the vertices used to represent this shape
    std::vector<Vector2> GetVertices() const override;

    // Returns the draw mode of this shape
    GLenum GetDrawMode() const override;

};

// Represents a line between 2 points in 2D space
class Line :  public Shape2D {

public:

    Vector2 a, b;

    // Constructors
    Line(Vector2 a, Vector2 b, Color color = Color::white) : Shape2D(color) {
        this->a = a;
        this->b = b;
    }
    Line() : Line(Vector2(0.0f, -0.5f), Vector2(0.0f, 0.5f)) {}

    // Destructors
    virtual ~Line() = default;

    // Returns the vertices used to represent this shape
    std::vector<Vector2> GetVertices() const override;

    // Returns the draw mode of this shape
    GLenum GetDrawMode() const override;

};

// Represents a line composed by connecting multiple points in 2D space
class Polyline : public Shape2D {

public:

    std::vector<Vector2> vertices;

    // Constructors
    Polyline(std::vector<Vector2> vertices, Color color = Color::white) : Shape2D(color) {
        this->vertices = vertices;
    }
    Polyline(Vector2 a, Vector2 b, Color color = Color::white) : Shape2D(color) {
        this->vertices.push_back(a);
        this->vertices.push_back(b);
    }
    Polyline() : Shape2D(Color::white) { this->vertices.clear(); }

    // Destructors
    virtual ~Polyline() = default;

    // Returns the vertices used to represent this shape
    std::vector<Vector2> GetVertices() const override;

    // Returns the draw mode of this shape
    GLenum GetDrawMode() const override;

};

// Represents a triangle in 2D space
class Triangle :  public Shape2D {

public:

    Vector2 a, b, c;

    // Constructors
    Triangle(Vector2 a, Vector2 b, Vector2 c, Color color = Color::white) : Shape2D(color) {
        this->a = a;
        this->b = b;
        this->c = c;
    }
    Triangle() : Triangle(Vector2(0.0f, 0.5f), Vector2(-0.5f, -0.5f), Vector2(0.5f, -0.5f)) {}

    Triangle(const Triangle& other) = default;
    Triangle(Triangle&& other) = default;

    Triangle& operator=(const Triangle& other) = default;
    Triangle& operator=(Triangle&& other) = default;

    // Destructors
    virtual ~Triangle() = default;

    // Returns the vertices used to represent this shape
    std::vector<Vector2> GetVertices() const override;

    // Returns the draw mode of this shape
    GLenum GetDrawMode() const override;

};

// Represents any shape with 4 sides in 2D space
class Quad :  public Shape2D {

public:

    Vector2 a, b, c, d;

    // Constructors
    Quad(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Color color = Color::white) : Shape2D(color) {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
    };
    Quad() : Quad(Vector2(0.5f, 0.5f), Vector2(-0.5f, 0.5f), Vector2(-0.5f, -0.5f), Vector2(0.5f, -0.5f)) {}

    // Destructors
    virtual ~Quad() = default;

    // Returns the vertices used to represent this shape
    std::vector<Vector2> GetVertices() const override;

    // Returns the draw mode of this shape
    GLenum GetDrawMode() const override;

};

// Represents a circle in 2D space
class Circle :  public Shape2D {

public:

    // Precision used to represent the circle when we need to convert it to 2D points
    int precision;
    
    // Default value for precision
    const static int default_precision = 32;

    Vector2 center;

    float radius;    

    // Constructors
    Circle(Vector2 center, float radius, int precision, Color color = Color::white) : Shape2D(color) {
        this->center = center;
        this->radius = radius;
        this->precision = precision;
    };
    Circle(Vector2 center, float radius) : Circle(center, radius, this->default_precision) {} 
    Circle() : Circle(Vector2(0.0f, 0.0f), 1.0f, this->default_precision) {}

    // Destructors
    virtual ~Circle() = default;

    // Returns the vertices used to represent this shape (an approximation of the Circle represented by a certain number of vertices)
    std::vector<Vector2> GetVertices() const override;

    // Returns the draw mode of this shape
    GLenum GetDrawMode() const override;

};

using Shape2DCollection = std::shared_ptr<std::vector<std::unique_ptr<Shape2D>>>;

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
    Triangle3D() : Triangle3D(Vector3(0.0f, 0.5f, 0.0f), Vector3(-0.5f, -0.5f, 0.0f), Vector3(0.5f, -0.5f, 0.0f)) {}    

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

# endif