// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

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
