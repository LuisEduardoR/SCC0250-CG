# include "Material.hpp"

# include "Renderer.hpp"
# include "../Assets/AssetLibrary.hpp"
#include "TextureObject.hpp"

Material::Material(std::shared_ptr<Shader> shader) : shader(shader) {}

auto Material::Bind() -> void
{
    Renderer::SetProgram(*shader.get());
}

DefaultMaterial::DefaultMaterial(
    std::shared_ptr<Shader> shader,
    const WavefrontMaterial& material)
    : Material(shader)
{
    ambientReflectivity = material.ambientReflectivity.value_or(Vector3{});
    diffuseReflectivity = material.diffuseReflectivity.value_or(Vector3{});
    specularReflectivity = material.specularReflectivity.value_or(Vector3{});
    specularExponent = material.specularExponent.value_or(0.0f);

    if (material.diffuseReflectivityMap.has_value()) {
        // TODO: Fix relative path workaround
        auto texture2d = AssetLibrary<Texture2D>::RequireAsset(
                "assets/" + material.diffuseReflectivityMap.value());

        texture = std::make_shared<TextureObject>(TextureObject::Type::Texture2D);
        texture->UploadTexture(0, texture2d);
    }
}

auto DefaultMaterial::Bind() -> void
{
    Material::Bind();

    glUniform1f(LOCATION_AMBIENT_REFLECTIVITY, ambientReflectivity.x);
    glUniform1f(LOCATION_DIFFUSE_REFLECTIVITY, diffuseReflectivity.x);
    glUniform1f(LOCATION_SPECULAR_REFLECTIVITY, specularReflectivity.x);
    glUniform1f(LOCATION_SPECULAR_EXPONENT, specularExponent);

    if (texture != nullptr)
    {
        GLint textureUnit{ 0 };
        // Texture unit to activate
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        // Binds texture to above texture unit.
        texture->Bind();

        // Texture unit to associate sampler with.
        glUniform1i(LOCATION_TEXTURE, textureUnit);
    }
}

SkyboxMaterial::SkyboxMaterial(
    std::shared_ptr<Shader> shader,
    std::shared_ptr<TextureObject> texture)
    : Material(shader), texture(texture) {}

auto SkyboxMaterial::Bind() -> void
{
    Material::Bind();

    if (texture != nullptr)
    {
        GLint textureUnit{ 0 };
        // Texture unit to activate
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        // Binds texture to above texture unit.
        texture->Bind();

        // Texture unit to associate sampler with.
        glUniform1i(LOCATION_TEXTURE, textureUnit);
    }
}
