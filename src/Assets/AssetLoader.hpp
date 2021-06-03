// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the base class to load assets
*/

# ifndef ASSET_LOADER_HPP
# define ASSET_LOADER_HPP

# include "../Rendering/Shader.hpp"
# include "../Rendering/Geometry2D.hpp"

# include <string>

template<typename T>
class AssetLoader {

public:

    // Constructos
    AssetLoader() = default;

    // Destructors
    virtual ~AssetLoader() = default;
    
    // Loads an asset from a file and returns it
    static T LoadAsset(const std::string& path);

    // Opens a file
    static std::ifstream OpenFile(const std::string& path);

    // Closes a file
    static void CloseFile(std::ifstream& file);

};

template<>
std::string AssetLoader<std::string>::LoadAsset(const std::string& path);

template<>
Shape2DCollection AssetLoader<Shape2DCollection>::LoadAsset(const std::string& path);

# endif /* end of include guard: ASSET_LOADER_HPP */
