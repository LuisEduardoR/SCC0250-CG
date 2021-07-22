# include "WavefrontMaterial.hpp"

# include <memory>
# include <fstream>

# include "AssetLibrary.hpp"
# include "FileOperations.hpp"
# include "WavefrontMaterialParser.hpp"

template<>
void AssetLibrary<WavefrontMaterial>::LoadAsset(const std::string& path) {

    std::ifstream file = OpenFile(path);
    std::vector<WavefrontMaterial> materials = WavefrontMaterialParser<>::ParseMaterials(file);
    for(auto&& material : materials) {
        library[material.materialName + '@' + path] = std::make_shared<WavefrontMaterial>(
            std::move(material)
        );
    }
    CloseFile(file);
}
