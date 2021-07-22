# include "WavefrontObject.hpp"

# include <memory>
# include <iostream>
# include <fstream>

# include "AssetLibrary.hpp"
# include "FileOperations.hpp"
# include "WavefrontObjectParser.hpp"

template<>
void AssetLibrary<WavefrontObject>::LoadAsset(const std::string& path) {

    std::cout << "Loading " << path << '\n';

    std::ifstream file = OpenFile(path);
    library[path] = std::make_shared<WavefrontObject>(
            WavefrontObjectParser<>::ParseObject(file)
    );
    CloseFile(file);

    std::cout << "LOADED " << path << '\n';
}
