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

    // Current program being used by the renderer
    static GLuint currentProgram;

    // Current array buffer bound to the renderer
    static GLuint arrayBuffer;

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
            TextureObject* texture = nullptr);

    void Renderer::DrawSkybox(
    const void* data,
    size_t data_size,
    size_t count,
    const Matrix4x4& transform,
    TextureObject* textureObject);
}; 

template<class T>
void Renderer::Draw(const T& object, const Matrix4x4& transform)
{
    // Draws a Shape applying a transformation matrix
    if constexpr (std::is_base_of_v<Shape, T>)
    {
        // Gets the vertices of our shape
        RenderData data = object.GetRenderData();

        // Performs the drawing
        DrawInternal((float*)data.vertices, data.vertexCount * sizeof(Vector2), data.vertexCount, data.drawMode, Color(*data.color), transform);
    }
    // Draws a ShapeCollection applying a transformation matrix
    else if constexpr (std::is_same_v<T, ShapeCollection>)
    {
        // Performs the drawing of each shape
        for (const std::unique_ptr<Shape>& shape : *object.get())
            Draw<Shape>(*shape.get(), transform);
    }
    // Draws a ShapeBatch applying a transformation matrix
    else if constexpr (std::is_same_v<T, ShapeBatch>)
    {
        // Performs the drawing of each state
        for(RenderStateChange state : object.stateChanges)
            DrawInternal((float*)(object.vertexBuffer.data() + state.index), state.vertexCount * sizeof(Vector2), state.vertexCount, state.drawMode, state.color, transform);

    }
    else if constexpr (std::is_same_v<T, Mesh>)
    {
        const std::vector<Mesh::VertexInput>& vertexInputBuffer(
            object.GetVertexInput()
        );

        int i = 0;
        for (const Mesh::DrawCall drawCall : object.GetDrawCalls())
        {
            float color = (float) i / (float) drawCall.count;

            DrawInternal(
                    // TODO: fix me
                    reinterpret_cast<const float*>(vertexInputBuffer.data() + drawCall.first),
                    sizeof(Mesh::VertexInput) * drawCall.count,
                    drawCall.count,
                    drawCall.mode,
                    Color(color, color, color),
                    transform,
                    object.GetTexture().get());
            i++;
        }
    }
    else
    {
        static_assert(AlwaysFalse<T>, "Unsupported object passed to Renderer::Draw");
    }
}

# endif /* end of include guard: RENDERER_HPP */
