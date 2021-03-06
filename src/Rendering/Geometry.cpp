// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Geometry.hpp"

# include <iostream>
#include <memory>
#include <stdexcept>
# include <unordered_set>

# include "Material.hpp"
# include "../Assets/AssetLibrary.hpp"
# include "../Assets/WavefrontMaterial.hpp"

Mesh::Mesh(std::vector<VertexInput>&& vertices) : vertexInputBuffer(std::move(vertices)) {}

Mesh::Mesh(const WavefrontObject& object)
{
    GLint start{ 0 };

    for (const WavefrontObject::Element<WavefrontObject::Face>& face : object.faces)
    {

        for (std::size_t i = 0; i < face.data.vertexIndexes.size(); i++)
        {
            VertexInput vertexInput{};

            vertexInput.position = Vector3
            {
                object.vertices.at(face.data.vertexIndexes[i] - 1).data
            };

            vertexInput.texturePosition = Vector2
            {
                object.textureVertices.at(face.data.textureVertexIndexes[i] - 1).data
            };

            vertexInput.normal = Vector3
            {
                object.normals.at(face.data.normalVectorIndexes[i] - 1).data
            };

            vertexInputBuffer.push_back(vertexInput);
        }

        GLint vertexCount{ static_cast<GLint>(face.data.vertexIndexes.size()) };
        drawCalls.push_back({ GL_TRIANGLE_FAN, start, vertexCount, nullptr });
        start += vertexCount;
    }
}

auto Mesh::GetVertexInput() const -> const std::vector<VertexInput>&
{
    return vertexInputBuffer;
}

auto Mesh::GetDrawCalls() const -> const std::vector<DrawCall>&
{
    return drawCalls;
}

auto Mesh::GetMaterial(std::size_t face) const -> std::shared_ptr<Material>
{
    return drawCalls.at(face).material;
}

auto Mesh::SetMaterial(std::size_t face, std::shared_ptr<Material> material) -> void
{
    drawCalls.at(face).material = material;
}
