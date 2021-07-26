# include "Material.hpp"

# include "Renderer.hpp"
# include "TextureObject.hpp"
# include "../Assets/AssetLibrary.hpp"
# include "../Components/Camera.hpp"
# include "../Components/GameObject.hpp"
# include "../Components/Light.hpp"
# include "../Components/Transform.hpp"

Material::Material(std::shared_ptr<Shader> shader) : shader(shader) {}

auto Material::Bind() -> void
{
    Renderer::SetProgram(*shader.get());
}

DefaultMaterial::DefaultMaterial(
    std::shared_ptr<Shader> shader,
    const WavefrontMaterial& material,
    std::shared_ptr<TextureObject> texture)
    : Material(shader), texture(texture)
{
    ambientReflectivity = material.ambientReflectivity.value_or(Vector3{});
    diffuseReflectivity = material.diffuseReflectivity.value_or(Vector3{});
    specularReflectivity = material.specularReflectivity.value_or(Vector3{});
    specularExponent = material.specularExponent.value_or(0.0f);
}

auto DefaultMaterial::Bind() -> void
{
    Material::Bind();

    Color ambientColor = Renderer::GetAmbientLightColor();

    glUniform1f(LOCATION_AMBIENT_REFLECTIVITY, ambientReflectivity.x * Renderer::GetAmbientLightIntensity());
    glUniform3f(LOCATION_AMBIENT_LIGHT_COLOR, ambientColor.r, ambientColor.g, ambientColor.b);
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

    for (std::size_t i = 0; i < Light::lights.size() && i < MAX_LIGHTS; i++)
    {
        if(auto* transform = Light::lights[i]->GetGameObject()->GetComponent<Transform>())
        {
            Vector3 position = transform->WorldPosition();
            Color color = Light::lights[i]->color;

            glUniform3f(LOCATION_LIGHTS + i * 6, position.x, position.y, position.z);
            glUniform3f(LOCATION_LIGHTS + i * 6 + 1, color.r, color.g, color.b);
        }
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
