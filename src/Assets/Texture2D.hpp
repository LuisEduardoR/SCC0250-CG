// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the code to load and represent 2D textures
*/

# ifndef TEXTURE2D_HPP
# define TEXTURE2D_HPP

# include <cstddef>
# include <memory>
# include <vector>

# include <GL/glew.h>

struct Texture2D final
{
public:
    enum PixelFormat : GLenum
    {
        R = GL_R,
        RG = GL_RG,
        RGB = GL_RGB,
        BGR = GL_BGR,
        RGBA = GL_RGBA,
        BGRA = GL_BGRA,
        DepthComponent = GL_DEPTH_COMPONENT,
        StencilIndex = GL_STENCIL_INDEX,
    };

    enum PixelType
    {
        U8 = GL_UNSIGNED_BYTE,
        U8_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
        U8_2_3_3_Rev = GL_UNSIGNED_BYTE_2_3_3_REV,
        U16 = GL_UNSIGNED_SHORT,
        U16_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
        U16_5_6_5_Rev = GL_UNSIGNED_SHORT_5_6_5_REV,
        U16_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
        U16_4_4_4_4_Rev = GL_UNSIGNED_SHORT_4_4_4_4_REV,
        U16_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
        U16_1_5_5_5_Rev = GL_UNSIGNED_SHORT_1_5_5_5_REV,
        U32 = GL_UNSIGNED_INT,
        U32_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
        U32_8_8_8_8_Rev = GL_UNSIGNED_INT_8_8_8_8_REV,
        U32_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2,
        U32_2_10_10_10_Rev = GL_UNSIGNED_INT_2_10_10_10_REV,
        I16 = GL_SHORT,
        I32 = GL_INT,
        F32 = GL_FLOAT,
    };

public:
    Texture2D(std::vector<std::byte>&& pixels,
            std::size_t width,
            std::size_t height,
            PixelFormat format,
            PixelType type);

    Texture2D(const Texture2D& other) = default;
    Texture2D(Texture2D&& other) = default;

    auto operator=(const Texture2D& other) -> Texture2D& = default;
    auto operator=(Texture2D&& other) -> Texture2D& = default;

    auto Format() const -> PixelFormat;

    /**
     * @returns The height of the image in pixels.
     */
    auto Height() const -> std::size_t;

    /**
     * @returns The length of a row of pixels in bytes.
     */
    auto Pitch() const -> std::size_t;

    auto Pixels() const -> const std::vector<std::byte>&;

    auto Type() const -> PixelType;

    /**
     * @returns The width of the image in pixels.
     */
    auto Width() const -> std::size_t;

private:
    std::size_t height;
    std::size_t width;
    std::size_t pitch;
    std::vector<std::byte> pixels;
    PixelFormat format;
    PixelType type;
};

# endif /* end of include guard: TEXTURE2D_HPP */
