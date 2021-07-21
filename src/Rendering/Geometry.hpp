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

class Mesh final {
public:
    // Shader input element
    struct VertexInput {
        Vector3 position;
        Vector2 texturePosition;
        Vector3 normal;
    };

    struct DrawCall {
        GLenum mode; // DrawMode
        GLint first; // Start index on the associated buffer
        GLsizei count; // Element count on the buffer
    };


    Mesh(std::vector<VertexInput>&& vertices);
    Mesh(std::shared_ptr<WavefrontObject> object);

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
