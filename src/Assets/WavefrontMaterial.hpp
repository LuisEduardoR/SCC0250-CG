# ifndef AMN_WAVEFRONT_MATERIAL_HPP
# define AMN_WAVEFRONT_MATERIAL_HPP

#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>
#include <string>

#include "../Math/Vector.hpp"

struct WavefrontMaterial final
{
    // newmtl
    std::string materialName;
    // Ka
    std::optional<Vector3> ambientReflectivity;
    // Kd
    std::optional<Vector3> diffuseReflectivity;
    // Ks
    std::optional<Vector3> specularReflectivity;
    // Ns
    std::optional<float> specularExponent;
    // Ke (blender extension)
    std::optional<Vector3> emission;

    // map_Kd
    std::optional<std::string> diffuseReflectivityMap;
};

/// Materials By Name
using WavefrontMaterialLibrary = std::unordered_map<std::string, WavefrontMaterial>;

# endif /* end of include guard: AMN_WAVEFRONT_MATERIAL_HPP */
