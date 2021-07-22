# include "WavefrontMaterial.hpp"

# include <memory>
# include <iostream>
# include <fstream>

# include "AssetLibrary.hpp"
# include "FileOperations.hpp"
# include "WavefrontMaterialParser.hpp"

template<>
void AssetLibrary<WavefrontMaterialLibrary>::LoadAsset(const std::string& path) {

    std::cout << "Loading " << path << '\n';

    std::ifstream file = OpenFile(path);
    std::vector<WavefrontMaterial> materials = WavefrontMaterialParser<>::ParseMaterials(file);
    WavefrontMaterialLibrary matLibrary{};
    for(auto&& material : materials) {

        matLibrary[material.materialName] = material;
    }

    library[path] = std::make_shared<WavefrontMaterialLibrary>(matLibrary);

    CloseFile(file);
    std::cout << "LOADED " << path << '\n';
}
