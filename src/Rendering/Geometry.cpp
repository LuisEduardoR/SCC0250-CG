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

Mesh::Mesh(const WavefrontObject& object, std::shared_ptr<Shader> shader)
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

        std::shared_ptr<Material> material{ nullptr };
        if (shader != nullptr && face.metadata.materialName != nullptr)
        {
            for (const auto& materialLibraryFile : object.materialLibraryFiles)
            {
                // TODO: Fix relative path workaround
                auto materialLibrary = AssetLibrary<WavefrontMaterialLibrary>
                    ::RequireAsset("assets/" + materialLibraryFile);

                try
                {
                    auto wMaterial = materialLibrary->at(*face.metadata.materialName);
                    material = std::make_shared<DefaultMaterial>(shader, wMaterial);
                }
                catch(const std::out_of_range&)
                {
                    continue;
                }

                break;
            }
        }

        GLint vertexCount{ static_cast<GLint>(face.data.vertexIndexes.size()) };
        drawCalls.push_back({ GL_TRIANGLE_FAN, start, vertexCount, material });
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

/* auto Mesh::GetMaterial() const -> std::shared_ptr<Material> */
/* { */
/*     return material; */
/* } */

/* auto Mesh::SetMaterial(std::shared_ptr<Material> material) -> void */
/* { */
/*     this->material = material; */
/* } */
