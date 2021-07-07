# include "TextureObject.hpp"

TextureObject::TextureObject(Type type) : type(type)
{
    glGenTextures(1, &self);
}

TextureObject::~TextureObject()
{
    glDeleteTextures(1, &self);
}

auto TextureObject::Bind() -> void
{
    glBindTexture(static_cast<GLenum>(type), self);
}

auto TextureObject::Unbind() -> void
{
    glBindTexture(static_cast<GLenum>(type), 0);
}

auto TextureObject::UploadTexture(GLint level, const Texture2D& textureAsset) -> void
{
    Bind();
    glTexImage2D(
            static_cast<GLenum>(type),
            level,
            GL_RGBA,
            static_cast<GLsizei>(textureAsset.Width()),
            static_cast<GLsizei>(textureAsset.Height()),
            0, // Always zero. Legacy stuff.
            static_cast<GLenum>(textureAsset.Format()),
            static_cast<GLenum>(textureAsset.Type()),
            textureAsset.Pixels().data());

    // Refactor this code into their own functions.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
}
