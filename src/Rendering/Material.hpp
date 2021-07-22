// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the base classes to represent 2D material
*/

# ifndef MATERIAL_HPP
# define MATERIAL_HPP

# define CONST_PI 3.14159265358979323846f


# include "../Assets/WavefrontMaterial.hpp"
# include "../Math/Vector.hpp"

# include <GL/glew.h>
# include <cmath>
# include <vector>
# include <memory>

union Matrix4x4;
class TextureObject;
class Shader;

class Material {
public:
    explicit Material(std::shared_ptr<Shader> shader);

    Material(const Material& other) = default;
    Material(Material&& other) = default;

    auto operator=(const Material& other) -> Material& = default;
    auto operator=(Material&& other) -> Material& = default;

    virtual ~Material() = default;
public:
    virtual auto Bind() -> void;
private:
    std::shared_ptr<Shader> shader;
};

struct Light final {
    Vector3 position;
    Vector3 color;
};

class DefaultMaterial : public Material {
public:
    static constexpr std::size_t MAX_LIGHTS{ 2 };

    // Transformation
    static constexpr GLint LOCATION_MODEL{ 0 };
    static constexpr GLint LOCATION_VIEW{ 1 };
    static constexpr GLint LOCATION_PROJECTION{ 2 };

    // Base color
    /* static constexpr GLint LOCATION_COLOR{ 3 }; */
    static constexpr GLint LOCATION_TEXTURE{ 4 };

    // Ambient Light
    static constexpr GLint LOCATION_AMBIENT_LIGHT_COLOR{ 5 };

    // Material Properties
    static constexpr GLint LOCATION_AMBIENT_REFLECTIVITY{ 6 };
    static constexpr GLint LOCATION_DIFFUSE_REFLECTIVITY{ 7 };
    static constexpr GLint LOCATION_SPECULAR_REFLECTIVITY{ 8 };
    static constexpr GLint LOCATION_SPECULAR_EXPONENT{ 9 };

    // Point Lights
    static constexpr GLint LOCATION_LIGHTS{ 10 };
public:
    DefaultMaterial(
        std::shared_ptr<Shader> shader,
        const WavefrontMaterial& material,
        std::shared_ptr<TextureObject> texture);

    DefaultMaterial(const DefaultMaterial& other) = default;
    DefaultMaterial(DefaultMaterial&& other) = default;

    auto operator=(const DefaultMaterial& other) -> DefaultMaterial& = default;
    auto operator=(DefaultMaterial&& other) -> DefaultMaterial& = default;

    ~DefaultMaterial() override = default;
public:
    auto Bind() -> void override;
private:
    /* Color color; */
    std::shared_ptr<TextureObject> texture;
    Vector3 ambientReflectivity;
    Vector3 diffuseReflectivity;
    Vector3 specularReflectivity;
    float specularExponent;
};


class SkyboxMaterial : public Material {
public:

    // Transformation
    static constexpr GLint LOCATION_VIEW{ 1 };

    // Base color
    static constexpr GLint LOCATION_TEXTURE{ 4 };
public:
    SkyboxMaterial(std::shared_ptr<Shader> shader, std::shared_ptr<TextureObject> texture);

    SkyboxMaterial(const SkyboxMaterial& other) = default;
    SkyboxMaterial(SkyboxMaterial&& other) = default;

    auto operator=(const SkyboxMaterial& other) -> SkyboxMaterial& = default;
    auto operator=(SkyboxMaterial&& other) -> SkyboxMaterial& = default;

    ~SkyboxMaterial() override = default;
public:
    auto Bind() -> void override;
private:
    std::shared_ptr<TextureObject> texture;
};

# endif /* end of include guard: MATERIAL_HPP */
