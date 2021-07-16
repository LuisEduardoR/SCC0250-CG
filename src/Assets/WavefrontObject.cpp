# include "WavefrontObject.hpp"

# include <memory>
# include <fstream>

# include "AssetLibrary.hpp"
# include "FileOperations.hpp"
# include "WavefrontParser.hpp"

template<>
void AssetLibrary<WavefrontObject>::LoadAsset(const std::string& path) {

    std::ifstream file = OpenFile(path);     
    library[path] = std::make_shared<WavefrontObject>(
        std::move(
            WavefrontParser<>::ParseObject(file)
        )
    );
    CloseFile(file);
}
