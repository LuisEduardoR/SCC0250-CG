# ifndef TEXTURE2D_HPP
# define TEXTURE2D_HPP

# include <cstddef>
# include <memory>
# include <vector>

struct Texture2D final
{
public:
    enum PixelFormat
    {
        R,
        RG,
        RGB,
        BGR,
        RGBA,
        BGRA,
        DepthComponent,
        StencilIndex,
    };

    enum PixelType
    {
        U8,
        U8_3_3_2,
        U8_2_3_3_Rev,
        U16,
        U16_5_6_5,
        U16_5_6_5_Rev,
        U16_4_4_4_4,
        U16_4_4_4_4_Rev,
        U16_5_5_5_1,
        U16_1_5_5_5_Rev,
        U32,
        U32_8_8_8_8,
        U32_8_8_8_8_Rev,
        U32_10_10_10_2,
        U32_2_10_10_10_Rev,
        I16,
        I32,
        F32,
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

    auto Format() -> PixelFormat;

    /**
     * @returns The height of the image in pixels.
     */
    auto Height() -> std::size_t;

    /**
     * @returns The length of a row of pixels in bytes.
     */
    auto Pitch() -> std::size_t;

    auto Type() -> PixelType;

    /**
     * @returns The width of the image in pixels.
     */
    auto Width() -> std::size_t;

private:
    std::size_t height;
    std::size_t width;
    std::size_t pitch;
    std::vector<std::byte> pixels;
    PixelFormat format;
    PixelType type;
};

# endif /* end of include guard: TEXTURE2D_HPP */
