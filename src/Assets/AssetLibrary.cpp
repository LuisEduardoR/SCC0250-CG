// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the base class to load assets
*/

# include "AssetLibrary.hpp"

# include "FileOperations.hpp"

# include <map>
# include <memory>
# include <stdexcept>
# include <cmath>
# include <iostream>
# include <fstream>
# include <sstream>

// Requires an asset from the library, if it is loaded just returns it, if not tries to load.
template<typename T>
std::shared_ptr<T> AssetLibrary<T>::RequireAsset(const std::string& path) {

    // If the asset is not in the library, tries loading it.
    if(library.count(path) < 1) {
        LoadAsset(path);
    }

    // Gets the asset from the library.
    return library[path];

}


template<>
void AssetLibrary<std::string>::LoadAsset(const std::string& path) {
   
    // Tries to open the file
    std::ifstream file = OpenFile(path);

    // Reads our entire file
    std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Closes the file
    CloseFile(file);

    // Adds the asset to library
    library[path] = std::make_shared<std::string>(std::move(contents));

}
