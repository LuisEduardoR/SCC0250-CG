// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the code to parse Wavefront materials (.mtl files)
*/

#ifndef AMN_WAVEFRONT_MATERIAL_PARSER_HPP
#define AMN_WAVEFRONT_MATERIAL_PARSER_HPP

#include <algorithm>
#include <array>
#include <exception>
#include <ios>
#include <istream>
#include <limits>
#include <locale>
#include <vector>
#include <stdexcept>
#include <string>

#include "WavefrontMaterial.hpp"
#include "WavefrontParser.hpp"
#include "../Math/Vector.hpp"
#include "../Utils/IOUtils.hpp"

template<
    typename Traits = std::char_traits<char>,
    typename Allocator = std::allocator<char>
>
class WavefrontMaterialParser : public WavefrontParser<Traits, Allocator>
{
    friend class WavefrontParserException;
public:
    // C++ always finds a way to get weirder.
    using base = WavefrontParser<Traits, Allocator>;
    using typename base::istream;
private:
    using typename base::string;

    using base::CR;
    using base::LF;
    using base::Space;
    using base::Tab;
    using base::BackSlash;
    using base::FwdSlash;
    using base::SpaceOrLineEnd;
    using base::LineEnd;

    using base::sourceStream;
public:
    /**
     *    @param sourceStream A stream of Wavefront material data, encoded in ASCII.
     */
    static auto ParseMaterials(istream& sourceStream) -> std::vector<WavefrontMaterial>;
private:
    explicit WavefrontMaterialParser(istream& sourceStream);
public:
    ~WavefrontMaterialParser() override = default;
private:
    auto ParseMaterials();
    auto ParseCoefficient() -> Vector3;
private:
    std::vector<WavefrontMaterial> materials;
};

template<typename Traits, typename Allocator>
auto WavefrontMaterialParser<Traits, Allocator>::ParseMaterials(
        istream& sourceStream)
    -> std::vector<WavefrontMaterial>
{
    WavefrontMaterialParser parser{ sourceStream };

    try
    {
        parser.ParseMaterials();
    }
    catch(...)
    {
        std::throw_with_nested(
                WavefrontParserException(parser, "Failed to parse Wavefront Material."));
    }

    return parser.materials;
}

template<typename Traits, typename Allocator>
WavefrontMaterialParser<Traits, Allocator>::WavefrontMaterialParser(
        istream& sourceStream)
    : WavefrontParser<Traits, Allocator>(sourceStream)
{
}


template<typename Traits, typename Allocator>
auto WavefrontMaterialParser<Traits, Allocator>::ParseMaterials()
{
    this->ForEachCommand([this](string command) {

        if (command == u8"newmtl")
        {
            ioutils::ReadWhile(sourceStream, { Space });

            if (!ioutils::Contains(LineEnd, sourceStream.peek()))
            {
                materials.push_back({});
                ioutils::ReadUntil(sourceStream, SpaceOrLineEnd, materials.back().materialName);
            }
            else throw WavefrontParserException(*this,
                    "map_Kd must specify a non empty filename.");
        }
        else if (materials.empty())
        {
            throw WavefrontParserException(*this,
                    std::string("Must declare a material before using this command: ")
                        + command + ".");
        }
        else if (command == u8"Ka")
        {
            materials.back().ambientReflectivity = ParseCoefficient();
        }
        else if (command == u8"Kd")
        {
            materials.back().diffuseReflectivity = ParseCoefficient();
        }
        else if (command == u8"Ks")
        {
            materials.back().specularReflectivity = ParseCoefficient();
        }
        else if (command == u8"Ke")
        {
            materials.back().emission = ParseCoefficient();
        }
        else if (command == u8"Ns")
        {
            ioutils::ReadWhile(sourceStream, { Space });
            float specularExponent;
            sourceStream >> specularExponent;
            materials.back().specularExponent = specularExponent;
        }
        else if (command == u8"map_Kd")
        {
            ioutils::ReadWhile(sourceStream, { Space });
            if (!ioutils::Contains(LineEnd, sourceStream.peek()))
            {
                std::string filename;
                ioutils::ReadUntil(sourceStream, SpaceOrLineEnd, filename);
                materials.back().diffuseReflectivityMap = std::move(filename);
            }
            else throw WavefrontParserException(*this,
                    "map_Kd must specify a non empty filename.");
        }
        else return false;

        return true;
    });
}

template<typename Traits, typename Allocator>
auto WavefrontMaterialParser<Traits, Allocator>::ParseCoefficient() -> Vector3
{
    Vector3 coefficient{};

    ioutils::ReadWhile(sourceStream, { Space });
    sourceStream >> coefficient.x;

    ioutils::ReadWhile(sourceStream, { Space });
    if (!ioutils::Contains(LineEnd, sourceStream.peek()))
    {
        sourceStream >> coefficient.y;
        ioutils::ReadWhile(sourceStream, { Space });
        sourceStream >> coefficient.z;
    }
    else
    {
        coefficient.y = coefficient.x;
        coefficient.z = coefficient.x;
    }

    return coefficient;
}

#endif /* end of include guard: AMN_WAVEFRONT_MATERIAL_PARSER__HPP */
