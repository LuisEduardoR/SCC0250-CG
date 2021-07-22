// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the base class to build asset libraries
*/

# ifndef ASSET_LIBRARY_HPP
# define ASSET_LIBRARY_HPP

# include "../Rendering/Geometry.hpp"
# include "../Rendering/Material.hpp"

# include <unordered_map>
# include <memory>
# include <string>

class Texture2D;

template<typename T>
class AssetLibrary {

public:

    // Constructors
    AssetLibrary() = default;

    // Destructors
    virtual ~AssetLibrary() = default;

    // Requires an asset from the library, if it is loaded just returns it, if not tries to load.
    static std::shared_ptr<T> RequireAsset(const std::string& path);

private:

    // Stores pointers to loaded assets.
    inline static std::unordered_map<std::string, std::shared_ptr<T>> library;

    // Loads an asset from a file and adds it to the library.
    static void LoadAsset(const std::string& path);

};

/*
 * Template classes.
 */

template class AssetLibrary<std::string>;
template class AssetLibrary<Texture2D>;
template class AssetLibrary<WavefrontObject>;
template class AssetLibrary<WavefrontMaterialLibrary>;

/*
 * Specializations. Might be defined on the T type cpp file.
 */

template<>
void AssetLibrary<std::string>::LoadAsset(const std::string& path);

template<>
void AssetLibrary<Texture2D>::LoadAsset(const std::string& path);

template<>
void AssetLibrary<WavefrontObject>::LoadAsset(const std::string& path);

template<>
void AssetLibrary<WavefrontMaterialLibrary>::LoadAsset(const std::string& path);

# endif /* end of include guard: ASSET_LIBRARY_HPP */
