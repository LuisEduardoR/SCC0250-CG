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
# include "Geometry.hpp"
# include "Color.hpp"

# include "../Math/Vector.hpp"
# include "../Math/Matrix4x4.hpp"

class Renderer {

public:

    // Initializes the renderer
    static void Init();

    // Destroy the render
    static void Destroy();

    // Clears our color program with a certain color
    static void Clear(const Color& color = Color::black);

    // Sets the program our renderer will use based on some shader code
    static void SetProgram(const std::string& vertexCode, const std::string& fragmentCode);

    // Sets the program our renderer will use from a shader
    static void SetProgram(const Shader& shader);

    // Sets the view matrix for the current program
    static void SetViewMatrix(const Matrix4x4& viewMatrix = Matrix4x4::Identity);

    // Draws an object of type T applying a transformation matrix
    template<class T>
    static void Draw(const T& object, const Matrix4x4& transform = Matrix4x4::Identity);

private:

    // Current program being used by the renderer
    static GLuint currentProgram;

    // Current array buffer bound to the renderer
    static GLuint arrayBuffer;

    // Creates an array buffer (if one was already created re-uses it)
    static void CreateArrayBuffer();

    // Draws an object directly interacting with our graphics API
    static void DrawInternal(float* data, size_t data_size, size_t count, GLenum mode, const Color& color = Color::white, const Matrix4x4& transform = Matrix4x4::Identity);

}; 

# endif /* end of include guard: RENDERER_HPP */
