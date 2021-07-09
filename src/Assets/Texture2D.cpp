# include "Texture2D.hpp"

# include <SDL2/SDL_image.h>
# include <SDL2/SDL_surface.h>
# include "AssetLoader.hpp"

# include <stdexcept>

template<>
auto AssetLoader<Texture2D>::LoadAsset(const std::string& filename) -> Texture2D
{
	// Load texture
	std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> image{
		IMG_Load(filename.data()),
		// Custom deleter, so we don't leak memory, even if an exception is thrown.
		SDL_FreeSurface	
	};

	if (image == nullptr)
	{
		std::string msg{ "Failed to load image from file: " };
		msg.append(filename);
		msg.append("\n\tDue to: ");
		msg.append(IMG_GetError());

		throw std::runtime_error(msg);
	}

	image.reset(SDL_ConvertSurfaceFormat(image.get(), SDL_PIXELFORMAT_RGBA32, 0)); 

	if (image == nullptr)
	{
		std::string msg{ "Failed to load image from file: " };
		msg.append(filename);
		msg.append("\n\tDue to: ");
		msg.append(IMG_GetError());

		throw std::runtime_error(msg);
	}

	std::size_t size = static_cast<std::size_t>(image->h * image->pitch);
	auto* begin = static_cast<const std::byte*>(image->pixels);
	auto* end = begin + size;

	std::vector<std::byte> pixels{};
	pixels.resize(size);

	SDL_LockSurface(image.get());
	std::copy(begin, end, pixels.begin());
	SDL_UnlockSurface(image.get());

	return Texture2D(std::move(pixels),
			static_cast<std::size_t>(image->w),
			static_cast<std::size_t>(image->h),
			Texture2D::PixelFormat::RGBA,
			Texture2D::PixelType::U8);
}

namespace
{

	auto PixelFormatNumComponents(Texture2D::PixelFormat format) -> std::size_t
	{
		switch(format)
		{
		case Texture2D::PixelFormat::R:
		case Texture2D::PixelFormat::DepthComponent:
		case Texture2D::PixelFormat::StencilIndex:
			return 1;
		case Texture2D::PixelFormat::RG:
			return 2;
		case Texture2D::PixelFormat::RGB:
		case Texture2D::PixelFormat::BGR:
			return 3;
		case Texture2D::PixelFormat::RGBA:
		case Texture2D::PixelFormat::BGRA:
			return 4;
		default:
			throw std::runtime_error("Invalid format!");
		}
	}

	auto PixelTypeBytes(Texture2D::PixelType type) -> std::size_t
	{
		switch(type)
		{
		case Texture2D::PixelType::U8:
		case Texture2D::PixelType::U8_2_3_3_Rev:
		case Texture2D::PixelType::U8_3_3_2:
			return 1;
		case Texture2D::PixelType::I16:
		case Texture2D::PixelType::U16:
		case Texture2D::PixelType::U16_1_5_5_5_Rev:
		case Texture2D::PixelType::U16_4_4_4_4:
		case Texture2D::PixelType::U16_4_4_4_4_Rev:
		case Texture2D::PixelType::U16_5_5_5_1:
		case Texture2D::PixelType::U16_5_6_5:
		case Texture2D::PixelType::U16_5_6_5_Rev:
			return 2;
		case Texture2D::PixelType::F32:
		case Texture2D::PixelType::I32:
		case Texture2D::PixelType::U32:
		case Texture2D::PixelType::U32_10_10_10_2:
		case Texture2D::PixelType::U32_2_10_10_10_Rev:
		case Texture2D::PixelType::U32_8_8_8_8:
		case Texture2D::PixelType::U32_8_8_8_8_Rev:
			return 4;
		default:
			throw std::runtime_error("Invalid format!");
		}
	}

}

Texture2D::Texture2D(std::vector<std::byte>&& pixels,
		std::size_t width,
		std::size_t height,
		PixelFormat format,
		PixelType type) : 
	height(height),
	width(width),
	pitch(width * PixelFormatNumComponents(format) *  PixelTypeBytes(type)),
	pixels(pixels),
	format(format),
	type(type)
{
	// TODO: Check invalid format and type combos.
}

auto Texture2D::Format() const -> PixelFormat { return format; }
auto Texture2D::Height() const -> std::size_t { return height; }
auto Texture2D::Pitch() const -> std::size_t { return pitch; }
auto Texture2D::Pixels() const -> const std::vector<std::byte>& { return pixels; }
auto Texture2D::Width() const -> std::size_t { return width; }
auto Texture2D::Type() const -> PixelType { return type; }
