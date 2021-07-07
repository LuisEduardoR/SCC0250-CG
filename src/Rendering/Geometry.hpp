// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the base classes to represent 2D geometry
*/

# ifndef GEOMETRY_HPP
# define GEOMETRY_HPP

# define CONST_PI 3.14159265358979323846f


# include "Color.hpp"
# include "RenderData.hpp"
# include "RenderStateChange.hpp"
# include "TextureObject.hpp"
# include "../Assets/WavefrontObject.hpp"
# include "../Math/Vector.hpp"

# include <GL/glew.h>
# include <cmath>
# include <vector>
# include <memory>
# include <algorithm>

class Shape {

public:

    Color color;

    // Constructors
    inline Shape(Color color) {
        this->color = color;
    }
    inline Shape() : Shape(Color::white) {}

    // Destructors
    virtual ~Shape() = default;

    // Returns te data necessary to render this shape
    virtual const RenderData GetRenderData() const = 0;

};

// Represents a point in 2D space
class Point :  public Shape {

public:

    Vector2 a;

    // Constructors
    inline Point(Vector2 a, Color color = Color::white) : Shape(color) {
        this->a = a;
    }
    inline Point() : Point(Vector2()) {}

    // Destructors
    virtual ~Point() = default;

    // Returns the data necessary to render this shape
    const RenderData GetRenderData() const override;

private:

    // The draw mode to be used for this shape
    GLuint drawMode = GL_POINTS;

};

// Represents a line between 2 points in 2D space
class Line :  public Shape {

public:

    Vector2 a, b;

    // Constructors
    inline Line(Vector2 a, Vector2 b, Color color = Color::white) : Shape(color) {
        this->a = a;
        this->b = b;
    }
    inline Line() : Line({ 0.0f, -0.5f}, { 0.0f, 0.5f}) {}

    // Destructors
    virtual ~Line() = default;

    // Returns the data necessary to render this shape
    const RenderData GetRenderData() const override;

private:

    // The draw mode to be used for this shape
    GLuint drawMode = GL_LINES;

};

// Represents a triangle in 2D space
class Triangle :  public Shape {

public:

    Vector2 a, b, c;

    // Constructors
    inline Triangle(Vector2 a, Vector2 b, Vector2 c, Color color = Color::white) : Shape(color) {
        this->a = a;
        this->b = b;
        this->c = c;
    }
    inline Triangle() : Triangle({ 0.0f, 0.5f}, { -0.5f, -0.5f}, { 0.5f, -0.5f}) {}

    Triangle(const Triangle& other) = default;
    Triangle(Triangle&& other) = default;

    Triangle& operator=(const Triangle& other) = default;
    Triangle& operator=(Triangle&& other) = default;

    // Destructors
    virtual ~Triangle() = default;

    // Returns the data necessary to render this shape
    const RenderData GetRenderData() const override;

private:

    // The draw mode to be used for this shape
    GLuint drawMode = GL_TRIANGLES;

};

// Represents any shape with 4 sides in 2D space
class Quad :  public Shape {

public:

    Vector2 a, b, c, d;

    // Constructors
    inline Quad(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Color color = Color::white) : Shape(color) {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
    };
    inline Quad() : Quad({ 0.5f, 0.5f}, { -0.5f, 0.5f}, { -0.5f, -0.5f}, { 0.5f, -0.5f}) {}

    // Destructors
    virtual ~Quad() = default;

    // Returns the data necessary to render this shape
    const RenderData GetRenderData() const override;

private:

    // The draw mode to be used for this shape
    GLuint drawMode = GL_TRIANGLE_STRIP;

};

// Represents a circle in 2D space
class Circle :  public Shape {

public:

    // Precision used to represent the circle when we need to convert it to 2D points
    int precision;
    
    // Default value for precision
    const static int default_precision = 32;

    Vector2 center;

    float radius;    

    // Constructors
    Circle(Vector2 center, float radius, int precision, Color color = Color::white) : Shape(color) {

        this->center = center;
        this->radius = radius;
        this->precision = precision;

        // Calculates some points to represent the circle
        GeneratePoints();
        
    }
    inline Circle(Vector2 center, float radius) : Circle(center, radius, this->default_precision) {} 
    inline Circle() : Circle({ 0.0f, 0.0f}, 1.0f, this->default_precision) {}

    // Destructors
    virtual ~Circle() = default;

    // Returns the data necessary to render this shape (an approximation of the Circle represented by a certain number of vertices is used)
    const RenderData GetRenderData() const override;

private:

    // Stores the vertices of the circle
    std::vector<Vector2> vertices{};

    // The draw mode to be used for this shape
    GLuint drawMode = GL_TRIANGLE_FAN;

    // Generates a number of points to represent an approximation of the circle based on precision
    // and saves them to vertices
    void GeneratePoints();

};

// Used to hold multiple Shapes together
using ShapeCollection = std::shared_ptr<std::vector<std::unique_ptr<Shape>>>;

// Used to batch lots of shapes together in order to render faster
class ShapeBatch {
    
public:

    ShapeBatch(ShapeCollection collection);

    // Stores the vertices of all Shapes batched together
    std::vector<Vector2> vertexBuffer;

    // Stores the data of all state changes that must happen when rendering
    std::vector<RenderStateChange> stateChanges;

};

class Mesh final {
public:
    // Shader input element
    struct VertexInput {
        Vector3 position;
        Vector2 texturePosition;
    };

    struct DrawCall {
        GLenum mode; // DrawMode
        GLint first; // Start index on the associated buffer
        GLsizei count; // Element count on the buffer
    };


    Mesh(std::vector<VertexInput>&& vertices);
    Mesh(const WavefrontObject& object);

    Mesh(const Mesh& other) = default;
    Mesh(Mesh&& other) = default;

    auto operator=(const Mesh& other) -> Mesh& = default;
    auto operator=(Mesh&& other) -> Mesh& = default;


    auto GetVertexInput() const -> const std::vector<VertexInput>&;
    auto GetDrawCalls() const -> const std::vector<DrawCall>&;
    auto GetTexture() const -> std::shared_ptr<TextureObject>;

    auto SetTexture(std::shared_ptr<TextureObject> texture) -> void;

private:
    std::vector<VertexInput> vertexInputBuffer;
    std::vector<DrawCall> drawCalls;
    std::shared_ptr<TextureObject> texture;
};

# endif /* end of include guard: GEOMETRY_HPP */
