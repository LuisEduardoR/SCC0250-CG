// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the class that handles the program's rendering
*/

# ifndef RENDERER_HPP
# define RENDERER_HPP

# include <GL/glew.h>

# include "Shader.hpp"
# include "Geometry2D.hpp"
# include "Geometry3D.hpp"
# include "Color.hpp"

# include "../Math/Vector.hpp"
# include "../Math/Matrix4x4.hpp"

class Renderer {

public:

    // Initializes the renderer
    static void Init();

    // Destroy the render
    static void Destroy();

    // Enables or disables 3D rendering    
    static void Set3D(bool enabled);
    
    // Clears our color buffer with a default color
    static void Clear();

    // Clears our color program with a certain color
    static void Clear(const Color& color);

    // Sets the program our renderer will use based on some shader code
    static void SetProgram(std::string vertex_code, std::string fragment_code);

    // ========================================================
    //
    // 2D
    //
    // ========================================================

    // Draws a Shape2D applying a transformation matrix
    static void DrawShape2D(const Shape2D& shape, const Matrix4x4& transform = Matrix4x4::Identity);

    // Draws a Shape2D applying a transformation matrix
    static void DrawShape2DCollection(const Shape2DCollection& shapes,
        const Matrix4x4& transform = Matrix4x4::Identity);

    // ========================================================
    //
    // 3D
    //
    // ========================================================

    // Draws a Mesh3D (uses the default transform matrix)
    static void DrawMesh3D(const Mesh3D& mesh, const Color& color);

    // Draws a Mesh3D applying a transformation matrix
    static void DrawMesh3D(const Mesh3D& mesh, const Color& color, const Matrix4x4& transform);

private:

    // Current program being used by the renderer
    static GLuint currentProgram;

    //Current array buffer bound to the renderer
    static GLuint arrayBuffer;

    // Creates an array buffer (if one was already created re-uses it)
    static void CreateArrayBuffer();

    // ========================================================
    //
    // 2D
    //
    // ========================================================

    // Draws a basic 2D shape (uses the default transform matrix)
    static void DrawBasic2D(float* data, size_t data_size, size_t count, GLenum mode, const Color& color);

    // Draws a basic 2D shape applying a transformation matrix
    static void DrawBasic2D(float* data, size_t data_size, size_t count, GLenum mode, const Color& color, const Matrix4x4& transform);

    // ========================================================
    //
    // 3D
    //
    // ========================================================

    // Draws a basic 3D shape (uses the default transform matrix)
    static void DrawBasic3D(float* data, size_t data_size, size_t count, GLenum mode, const Color& color);

    // Draws a basic 3D shape applying a transformation matrix
    static void DrawBasic3D(float* data, size_t data_size, size_t count, GLenum mode, const Color& color, const Matrix4x4& transform);

}; 

# endif /* end of include guard: RENDERER_HPP */
