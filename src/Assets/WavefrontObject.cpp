# include "WavefrontObject.hpp"

# include <fstream>

# include "AssetLoader.hpp"
# include "WavefrontParser.hpp"

template<>
WavefrontObject AssetLoader<WavefrontObject>::LoadAsset(const std::string& path)
{
    std::ifstream file = OpenFile(path);     
    WavefrontObject obj = WavefrontParser<>::ParseObject(file);
    CloseFile(file);

    return obj;
}
