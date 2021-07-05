#ifndef AMN_WAVEFRONT_PARSER_HPP
#define AMN_WAVEFRONT_PARSER_HPP

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
#include "../Math/Vector.hpp"
#include "../Utils/IOUtils.hpp"

template<
	typename Traits = std::char_traits<char>,
	typename Allocator = std::allocator<char>
>
class WavefrontParser final
{
	friend class WavefrontParserException;
private:
	static constexpr auto CR = Traits::to_int_type(u8'\r');

	static constexpr auto LF = Traits::to_int_type(u8'\n');

	static constexpr auto Space = Traits::to_int_type(u8' ');

	static constexpr auto Tab = Traits::to_int_type(u8'\t');

	static constexpr auto BackSlash = Traits::to_int_type(u8'\\');

	static constexpr auto FwdSlash = Traits::to_int_type(u8'/');

	static constexpr std::array<typename Traits::int_type, 3> SpaceOrLineEnd
	{{
		Space, LF, CR
	}};

	static constexpr std::array<typename Traits::int_type, 2> LineEnd
	{{
		LF, CR
	}};
public:
	/**
	 *	@param sourceStream A stream of Wavefront object data, encoded in ASCII.
	 */
	static auto ParseObject(std::basic_istream<char, Traits>& sourceStream) -> WavefrontObject;
private:
	explicit WavefrontParser(std::basic_istream<char, Traits>& sourceStream);

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
	std::size_t currentLine = 1;
	typename Traits::pos_type lineStartPos;
	std::basic_istream<char, Traits>& sourceStream;
	std::basic_string<char, Traits, Allocator> command{};
	WavefrontObject object{};
	WavefrontObject::ElementMetadata elementMetadata{};
};

class WavefrontParserException : public std::runtime_error
{
public:

	template<typename Traits, typename Allocator>
	inline explicit WavefrontParserException(
			const WavefrontParser<Traits, Allocator>& parser,
			const char* message)
		: std::runtime_error(std::string("WavefrontParser: at ")
				+ std::to_string(parser.currentLine) + ':'
				+ std::to_string(parser.sourceStream.tellg() - parser.lineStartPos) + '\n'
				+ message) {}

	WavefrontParserException(const WavefrontParserException&) noexcept = default;

	~WavefrontParserException() override = default;
	
	auto operator=(const WavefrontParserException&) noexcept
		-> WavefrontParserException& = default;
};

template<typename Traits, typename Allocator>
auto WavefrontParser<Traits, Allocator>::ParseObject(
		std::basic_istream<char, Traits>& sourceStream)
	-> WavefrontObject
{
	WavefrontParser parser{ sourceStream };

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
WavefrontParser<Traits, Allocator>::WavefrontParser(
		std::basic_istream<char, Traits>& sourceStream)
	: sourceStream(sourceStream)
{
	// Force ASCII, C number format.
	sourceStream.imbue(std::locale("C"));
	sourceStream.exceptions(std::ios_base::failbit | std::ios_base::badbit);
	sourceStream.flags(std::ios_base::dec);
	sourceStream.seekg(0, std::ios_base::beg);

	lineStartPos = sourceStream.tellg();
}


template<typename Traits, typename Allocator>
auto WavefrontParser<Traits, Allocator>::ParseObject()
{
	std::basic_string<char, Traits, Allocator> command{};

	while(!sourceStream.eof())
	{
		lineStartPos = sourceStream.tellg();
		ioutils::ReadWhile(sourceStream, { Space, Tab });
		ioutils::ReadUntil(sourceStream, SpaceOrLineEnd, command);

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
		else if (command.size() > 0 && command[0] == u8'#')
		{
		}
		else
		{
			std::cout << "Unknown Wavefront Object command at line "
				<< currentLine << ", column "
				<< sourceStream.tellg() - lineStartPos
				<< ", skipping.\n";
		}

		ioutils::ReadUntil(sourceStream, LineEnd);
		ioutils::ReadWhile(sourceStream, LineEnd);

		command.clear();
		currentLine += 1;
	}
}

template<typename Traits, typename Allocator>
auto WavefrontParser<Traits, Allocator>::ParseVertex()
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
auto WavefrontParser<Traits, Allocator>::ParseNormalVector()
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
auto WavefrontParser<Traits, Allocator>::ParseTextureVertex()
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
auto WavefrontParser<Traits, Allocator>::ParseFace()
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
auto WavefrontParser<Traits, Allocator>::ParseMaterialLibrary()
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
auto WavefrontParser<Traits, Allocator>::ParseObjectName()
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
auto WavefrontParser<Traits, Allocator>::ParseGroupNames()
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

#endif /* end of include guard: AMN_WAVEFRONT_PARSER__HPP */
