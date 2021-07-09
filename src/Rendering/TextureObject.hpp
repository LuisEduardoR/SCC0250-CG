# ifndef TEXTURE_OBJECT_HPP
# define TEXTURE_OBJECT_HPP

# include "../Assets/Texture2D.hpp"
# include "GLObject.hpp"

class TextureObject : public GLObject
{
public:
    enum class Type : GLenum
    {
        Texture1D = GL_TEXTURE_1D,
        Texture2D = GL_TEXTURE_2D,
        Texture3D = GL_TEXTURE_3D,
        TextureRectangle = GL_TEXTURE_RECTANGLE,
        TextureBuffer = GL_TEXTURE_BUFFER,
        TextureCubeMap = GL_TEXTURE_CUBE_MAP,
        Texture2DMultiSample = GL_TEXTURE_2D_MULTISAMPLE,

        Texture1DArray = GL_TEXTURE_1D_ARRAY,
        Texture2DArray = GL_TEXTURE_2D_ARRAY,
        TextureCubeMapArray = GL_TEXTURE_CUBE_MAP_ARRAY,
        Texture2DMultiSampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
    };

public:
    TextureObject(Type type);
    TextureObject(TextureObject&& other) = default;
    auto operator=(TextureObject&& other) -> TextureObject& = default;
    ~TextureObject();

    auto Bind() -> void;
    auto Unbind() -> void;
    auto UploadTexture(GLint level, const Texture2D& textureAsset) -> void; 
    auto UploadTexture(GLint level, const std::array<Texture2D, 6>& textureAssets) -> void;

    Type type;
};

# endif /* end of include guard: TEXTURE_OBJECT_HPP */
