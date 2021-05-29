// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# ifndef RENDERER_HPP
# define RENDERER_HPP

# include <GL/glew.h>
# include <iostream>

# include "Shader.hpp"
# include "Geometry.hpp"
# include "Color.hpp"

/*
    This file contains the classes that handles the program's rendering
*/

class Renderer {

public:

    // Constructor
    Renderer(bool enable3D);
    Renderer() : Renderer(true) {};

    // Destructor
    ~Renderer();
    
    // Clears our color buffer with a default color
    void Clear();

    // Clears our color program with a certain color
    void Clear(const Color& color);

    // Sets the program our renderer will use based on some shader code
    void SetProgram(std::string vertex_code, std::string fragment_code);

    // 2D =====================================

    // Draws a basic 2D shape (uses the default transform matrix)
    void DrawBasic2D(float* data, size_t data_size, size_t count, GLenum mode, const Color& color);

    // Draws a basic 2D shape applying a transformation matrix
    void DrawBasic2D(float* data, size_t data_size, size_t count, GLenum mode, const Color& color, const Matrix4& transform);

    // Functions to draw some of our basic geometry (uses the default transform matrix):

    void DrawPoint(const Vector2& vec, const Color& color);
    void DrawLine(const Line& line, const Color& color);
    void DrawPolyline(const Polyline& polyline, const Color& color);
    void DrawTriangle(const Triangle& triangle, const Color& color);
    void DrawQuad(const Quad& quad, const Color& color);
    void DrawCircle(const Circle& circle, const Color& color);

    // Functions to draw some of our basic geometry applying transformation matrixes:

    void DrawPoint(const Vector2& vec, const Color& color, const Matrix4& transform);
    void DrawLine(const Line& line, const Color& color, const Matrix4& transform);
    void DrawPolyline(const Polyline& polyline, const Color& color, const Matrix4& transform);
    void DrawTriangle(const Triangle& triangle, const Color& color, const Matrix4& transform);
    void DrawQuad(const Quad& quad, const Color& color, const Matrix4& transform);
    void DrawCircle(const Circle& circle, const Color& color, const Matrix4& transform);

    // 3D =====================================

    // Draws a basic 3D shape (uses the default transform matrix)
    void DrawBasic3D(float* data, size_t data_size, size_t count, GLenum mode, const Color& color);

    // Draws a basic 3D shape applying a transformation matrix
    void DrawBasic3D(float* data, size_t data_size, size_t count, GLenum mode, const Color& color, const Matrix4& transform);

    // Functions to draw some of our basic geometry (uses the default transform matrix):

    void DrawMesh3D(const Mesh3D& mesh, const Color& color);

    // Functions to draw some of our basic geometry applying transformation matrixes:

    void DrawMesh3D(const Mesh3D& mesh, const Color& color, const Matrix4& transform);

private:

    // Current program being used by the renderer
    GLuint currentProgram;

    //Current array buffer bound to the renderer
    GLuint arrayBuffer;

    // Creates an array buffer (if one was already created re-uses it)
    void CreateArrayBuffer();

};
 

# endif