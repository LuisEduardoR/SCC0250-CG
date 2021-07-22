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
# include <type_traits>

# include "Shader.hpp"
# include "Geometry.hpp"
# include "Color.hpp"
# include "TextureObject.hpp"

# include "../Math/Vector.hpp"
# include "../Math/Matrix4x4.hpp"
# include "../Utils/TypeUtils.hpp"

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
    //
    // Sets the projection matrix for the current program
    static void SetProjectionMatrix(const Matrix4x4& projectionMatrix = Matrix4x4::Identity);

    // Draws an object of type T applying a transformation matrix
    template<class T>
    static void Draw(const T& object, const Matrix4x4& transform = Matrix4x4::Identity);

    // Toggles wireframe rendering.
    static void ToggleWireframe();

private:
    static bool wireframeMode;

    static Matrix4x4 projection;

    static Matrix4x4 view;

    // Current program being used by the renderer
    static GLuint currentProgram;

    // Current vertex array buffer (VBO) bound to the renderer
    static GLuint vertexBuffer;

    // Current vertex array (VAO) bound to the renderer
    static GLuint vertexArray;

    // Creates an array buffer (if one was already created re-uses it)
    static void CreateArrayBuffer();

    // Draws an object directly interacting with our graphics API
    static void DrawInternal(
            const void* data,
            size_t data_size,
            size_t count,
            GLenum mode,
            const Color& color = Color::white,
            const Matrix4x4& transform = Matrix4x4::Identity,
            Material* material = nullptr);
public:
    static void DrawSkybox(
            const void* data,
            size_t data_size,
            size_t count,
            const Matrix4x4& transform,
            TextureObject* texture);
};

template<class T>
void Renderer::Draw(const T& object, const Matrix4x4& transform) {

    // Draws a mesh applying the necessary matrixes
    if constexpr (std::is_same_v<T, Mesh>)
    {
        // Gets the data for rendering (positions and UVs)
        const std::vector<Mesh::VertexInput>& vertexInputBuffer(
            object.GetVertexInput()
        );

        // Draws each face of an object
        for (const Mesh::DrawCall drawCall : object.GetDrawCalls())
        {

            // Performs the drawing
            DrawInternal(
                            vertexInputBuffer.data() + drawCall.first,
                            sizeof(Mesh::VertexInput) * drawCall.count,
                            drawCall.count,
                            drawCall.mode,
                            Color::white,
                            transform,
                            drawCall.material.get()
                        );

        }
    }
    else
    {
        static_assert(AlwaysFalse<T>, "Unsupported object passed to Renderer::Draw");
    }
}

# endif /* end of include guard: RENDERER_HPP */
