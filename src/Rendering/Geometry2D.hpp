// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the base classes to represent 2D geometry
*/

# ifndef GEOMETRY2D_HPP
# define GEOMETRY2D_HPP

# define CONST_PI 3.14159265358979323846f


# include "Color.hpp"
# include "VertexData.hpp"
# include "../Math/Vector.hpp"

# include <GL/glew.h>
# include <cmath>
# include <vector>
# include <memory>

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
    virtual const VertexData GetVertices() const = 0;

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
    const VertexData GetVertices() const override;

    // Returns the draw mode of this shape
    GLenum GetDrawMode() const override;

};

// Represents a cluster of points in 2D space
class PointCluster :  public Shape2D {

public:

    // Constructors
    PointCluster(std::vector<Vector2> vertices, Color color = Color::white)
        : Shape2D(color), vertices(std::move(vertices)) {}

    PointCluster() : Shape2D(Color::white) {}

    // Destructors
    virtual ~PointCluster() = default;

    // Returns the vertices used to represent this shape
    const VertexData GetVertices() const override;

    // Returns the draw mode of this shape
    GLenum GetDrawMode() const override;

private:

    // Stores the vertices of the point cluster
    std::vector<Vector2> vertices{};

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
    Line() : Line({ 0.0f, -0.5f}, { 0.0f, 0.5f}) {}

    // Destructors
    virtual ~Line() = default;

    // Returns the vertices used to represent this shape
    const VertexData GetVertices() const override;

    // Returns the draw mode of this shape
    GLenum GetDrawMode() const override;

};

// Represents a line composed by connecting multiple points in 2D space
class Polyline : public Shape2D {

public:

    // Constructors
    Polyline(std::vector<Vector2> vertices, Color color = Color::white)
        : Shape2D(color), vertices(std::move(vertices)) {
    }
    Polyline(Vector2 a, Vector2 b, Color color = Color::white) : Polyline({a, b}, color) {}
    Polyline() : Shape2D(Color::white) {}

    // Destructors
    virtual ~Polyline() = default;

    // Returns the vertices used to represent this shape
    const VertexData GetVertices() const override;

    // Returns the draw mode of this shape
    GLenum GetDrawMode() const override;

private:

    // Stores the vertices of the polyline
    std::vector<Vector2> vertices{};

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
    Triangle() : Triangle({ 0.0f, 0.5f}, { -0.5f, -0.5f}, { 0.5f, -0.5f}) {}

    Triangle(const Triangle& other) = default;
    Triangle(Triangle&& other) = default;

    Triangle& operator=(const Triangle& other) = default;
    Triangle& operator=(Triangle&& other) = default;

    // Destructors
    virtual ~Triangle() = default;

    // Returns the vertices used to represent this shape
    const VertexData GetVertices() const override;

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
    Quad() : Quad({ 0.5f, 0.5f}, { -0.5f, 0.5f}, { -0.5f, -0.5f}, { 0.5f, -0.5f}) {}

    // Destructors
    virtual ~Quad() = default;

    // Returns the vertices used to represent this shape
    const VertexData GetVertices() const override;

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

        // Calculates some points to represent the circle
        this->vertices.reserve(precision);
        float angle = 0.0;
        for(int i = 0; i < this->precision; i++){
            angle += (2.0f * CONST_PI) / this->precision;
            float x = this->center.x + std::cos(angle) * this->radius;
            float y = this->center.y + std::sin(angle) * this->radius;
            this->vertices.push_back({ x, y });
        }
        
    }
    Circle(Vector2 center, float radius) : Circle(center, radius, this->default_precision) {} 
    Circle() : Circle({ 0.0f, 0.0f}, 1.0f, this->default_precision) {}

    // Destructors
    virtual ~Circle() = default;

    // Returns the vertices used to represent this shape (an approximation of the Circle represented by a certain number of vertices)
    const VertexData GetVertices() const override;

    // Returns the draw mode of this shape
    GLenum GetDrawMode() const override;

private:

    // Stores the vertices of the circle
    std::vector<Vector2> vertices{};

};

using Shape2DCollection = std::shared_ptr<std::vector<std::unique_ptr<Shape2D>>>;

# endif /* end of include guard: GEOMETRY2D_HPP */