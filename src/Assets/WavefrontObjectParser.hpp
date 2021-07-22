#ifndef AMN_WAVEFRONT_OBJECT_PARSER_HPP
#define AMN_WAVEFRONT_OBJECT_PARSER_HPP

#include <algorithm>
#include <array>
#include <exception>
#include <ios>
#include <istream>
#include <limits>
#include <locale>
#include <stdexcept>
#include <string>

#include "WavefrontObject.hpp"
#include "WavefrontParser.hpp"
#include "../Math/Vector.hpp"
#include "../Utils/IOUtils.hpp"

template<
    typename Traits = std::char_traits<char>,
    typename Allocator = std::allocator<char>
>
class WavefrontObjectParser : public WavefrontParser<Traits, Allocator>
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
     *    @param sourceStream A stream of Wavefront object data, encoded in ASCII.
     */
    static auto ParseObject(istream& sourceStream) -> WavefrontObject;
private:
    explicit WavefrontObjectParser(istream& sourceStream);
public:
    ~WavefrontObjectParser() override = default;
private:
    auto ParseObject();
    auto ParseVertex();
    auto ParseNormalVector();
    auto ParseTextureVertex();
    auto ParseFace();
    auto ParseMaterialLibrary();
    auto ParseObjectName();
    auto ParseGroupNames();
    auto ParseSmoothingGroup();
    auto ParseMergeGroup();
private:
    WavefrontObject object{};
    WavefrontObject::ElementMetadata elementMetadata{};
};

template<typename Traits, typename Allocator>
auto WavefrontObjectParser<Traits, Allocator>::ParseObject(
        istream& sourceStream)
    -> WavefrontObject
{
    WavefrontObjectParser parser{ sourceStream };

    try
    {
        parser.ParseObject();
    }
    catch(...)
    {
        std::throw_with_nested(
                WavefrontParserException(parser, "Failed to parse Wavefront Object."));
    }

    return parser.object;
}

template<typename Traits, typename Allocator>
WavefrontObjectParser<Traits, Allocator>::WavefrontObjectParser(
        istream& sourceStream)
    : WavefrontParser<Traits, Allocator>(sourceStream)
{
}


template<typename Traits, typename Allocator>
auto WavefrontObjectParser<Traits, Allocator>::ParseObject()
{
    this->ForEachCommand([this](string command) {

        if (command == u8"v")
        {
            ParseVertex();
        }
        else if (command == u8"vn")
        {
            ParseNormalVector();
        }
        else if (command == u8"vt")
        {
            ParseTextureVertex();
        }
        else if (command == u8"f")
        {
            ParseFace();
        }
        else if (command == u8"mtllib")
        {
            ParseMaterialLibrary();
        }
        else if (command == u8"o")
        {
            ParseObjectName();
        }
        else if (command == u8"g")
        {
            ParseGroupNames();
        }
        else return false;

        return true;
    });
}

template<typename Traits, typename Allocator>
auto WavefrontObjectParser<Traits, Allocator>::ParseVertex()
{
    Vector4 vertex{};

    ioutils::ReadWhile(sourceStream, { Space });
    sourceStream >> vertex.x;
    ioutils::ReadWhile(sourceStream, { Space });
    sourceStream >> vertex.y;
    ioutils::ReadWhile(sourceStream, { Space });
    sourceStream >> vertex.z;

    ioutils::ReadWhile(sourceStream, { Space });
    if (ioutils::Contains(LineEnd, sourceStream.peek()))
    {
        vertex.w = 1.0f;
    }
    else
    {
        sourceStream >> vertex.w;
    }

    object.vertices.push_back({ elementMetadata, vertex });
}

template<typename Traits, typename Allocator>
auto WavefrontObjectParser<Traits, Allocator>::ParseNormalVector()
{
    Vector3 normal{};

    ioutils::ReadWhile(sourceStream, { Space });
    sourceStream >> normal.x;
    ioutils::ReadWhile(sourceStream, { Space });
    sourceStream >> normal.y;
    ioutils::ReadWhile(sourceStream, { Space });
    sourceStream >> normal.z;

    object.normals.push_back({ elementMetadata, normal });
}

template<typename Traits, typename Allocator>
auto WavefrontObjectParser<Traits, Allocator>::ParseTextureVertex()
{
    Vector3 textureVertex{};

    ioutils::ReadWhile(sourceStream, { Space });
    sourceStream >> textureVertex.x;
    ioutils::ReadWhile(sourceStream, { Space });
    sourceStream >> textureVertex.y;
    ioutils::ReadWhile(sourceStream, { Space });
    if (ioutils::Contains(LineEnd, sourceStream.peek()))
    {
        textureVertex.z = 0.0f;
    }
    else
    {
        sourceStream >> textureVertex.z;
    }

    object.textureVertices.push_back({ elementMetadata, textureVertex });
}

template<typename Traits, typename Allocator>
auto WavefrontObjectParser<Traits, Allocator>::ParseFace()
{
    auto assertTextureVertexSpecifyAllowed = [this](const WavefrontObject::Face& face) -> void
    {
        if (!face.vertexIndexes.empty() && face.textureVertexIndexes.empty())
        {
            throw WavefrontParserException(*this,
                    "Vertex data for a face must be consistent: "
                    "Texture vertex was previously omitted, can't be specified now."
                    "\n\tEither omit all texture vertices or specify them all.");
        }
    };

    auto assertTextureVertexOmitAllowed = [this](const WavefrontObject::Face& face) -> void
    {
        if (!face.vertexIndexes.empty() && !face.textureVertexIndexes.empty())
        {
            throw WavefrontParserException(*this,
                    "Vertex data for a face must be consistent: "
                    "Texture vertex was previously specified, can't be omitted now."
                    "\n\tEither specify all texture vertices or omit them all.");
        }
    };

    auto assertNormalVectorSpecifyAllowed = [this](const WavefrontObject::Face& face) -> void
    {
        if (!face.vertexIndexes.empty() && face.normalVectorIndexes.empty())
        {
            throw WavefrontParserException(*this,
                    "Vertex data for a face must be consistent: "
                    "Normal vector was previously omitted, can't be specified now."
                    "\n\tEither omit all normal vectors or specify them all.");
        }
    };

    auto assertNormalVectorOmitAllowed = [this](const WavefrontObject::Face& face) -> void
    {
        if (!face.vertexIndexes.empty() && !face.normalVectorIndexes.empty())
        {
            throw WavefrontParserException(*this,
                    "Vertex data for a face must be consistent: "
                    "Normal vector was previously specified, can't be omitted now."
                    "\n\tEither specify all normal vectors or omit them all.");
        }
    };

    WavefrontObject::Face face{};

    while (!ioutils::Contains(LineEnd, sourceStream.peek()))
    {
        ioutils::ReadWhile(sourceStream, { Space });

        std::size_t vertexIndex;
        sourceStream >> vertexIndex;

        if (sourceStream.peek() == FwdSlash)
        {
            sourceStream.seekg(1, std::ios_base::cur);

            if (sourceStream.peek() != FwdSlash)
            {
                assertTextureVertexSpecifyAllowed(face);

                std::size_t textureVertexIndex;
                sourceStream >> textureVertexIndex;

                face.textureVertexIndexes.push_back(textureVertexIndex);
            }
            else
            {
                assertTextureVertexOmitAllowed(face);
            }

            if (sourceStream.peek() == FwdSlash)
            {
                assertNormalVectorSpecifyAllowed(face);

                sourceStream.seekg(1, std::ios_base::cur);

                std::size_t normalVectorIndex;
                sourceStream >> normalVectorIndex;

                face.normalVectorIndexes.push_back(normalVectorIndex);
            }
            else
            {
                assertNormalVectorOmitAllowed(face);
            }
        }
        else
        {
            assertTextureVertexOmitAllowed(face);
            assertNormalVectorOmitAllowed(face);
        }

        face.vertexIndexes.push_back(vertexIndex);
    }

    object.faces.push_back({ elementMetadata, face });
}

template<typename Traits, typename Allocator>
auto WavefrontObjectParser<Traits, Allocator>::ParseMaterialLibrary()
{
    if (!object.materialLibraryFiles.empty())
    {
        throw WavefrontParserException(*this,
                "mtllib command can only be used once per file");
    }

    ioutils::ReadWhile(sourceStream, { Space });
    for (auto nextValue = sourceStream.peek();
            nextValue != LF && nextValue != CR; nextValue = sourceStream.peek())
    {
        std::string filename;
        ioutils::ReadUntil(sourceStream, SpaceOrLineEnd, filename);

        if (!filename.empty())
        {
            object.materialLibraryFiles.push_back(filename);
        }
        else
        {
            throw WavefrontParserException(*this,
                    "Must specify at least one filename for mtllib command\n"
                    "\tformat: mtllib filename1 filename2 ... filenameN");
        }

        ioutils::ReadWhile(sourceStream, { Space });
    }
}

template<typename Traits, typename Allocator>
auto WavefrontObjectParser<Traits, Allocator>::ParseObjectName()
{
    ioutils::ReadWhile(sourceStream, { Space });
    std::string filename;
    ioutils::ReadUntil(sourceStream, SpaceOrLineEnd, filename);

    if (!filename.empty())
    {
        elementMetadata.objectName = std::make_shared<std::string>(filename);
    }
    else
    {
        throw WavefrontParserException(*this,
                "Must specify object name for o command\n"
                "\tformat: o object_name");
    }
}

template<typename Traits, typename Allocator>
auto WavefrontObjectParser<Traits, Allocator>::ParseGroupNames()
{
    std::vector<std::string> groups{};

    ioutils::ReadWhile(sourceStream, { Space });
    for (auto nextValue = sourceStream.peek();
            nextValue != LF && nextValue != CR; nextValue = sourceStream.peek())
    {
        std::string groupName;
        ioutils::ReadUntil(sourceStream, SpaceOrLineEnd, groupName);

        if (!groupName.empty())
        {
            groups.push_back(groupName);
        }
        else
        {
            throw WavefrontParserException(*this,
                    "Must specify at least one group name for g command\n"
                    "\tformat: g groupName1 groupName2 ... groupNameN");
        }

        ioutils::ReadWhile(sourceStream, { Space });
    }

    elementMetadata.groupNames = std::make_shared<std::vector<std::string>>(groups);
}

#endif /* end of include guard: AMN_WAVEFRONT_OBJECT_PARSER__HPP */
