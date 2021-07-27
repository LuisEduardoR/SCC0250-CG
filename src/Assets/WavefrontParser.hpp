// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the code to parse Wavefront files (both .obj and .mtl)
*/

#ifndef AMN_WAVEFRONT_PARSER_HPP
#define AMN_WAVEFRONT_PARSER_HPP

#include <algorithm>
#include <array>
#include <exception>
#include <functional>
#include <ios>
#include <istream>
#include <limits>
#include <locale>
#include <stdexcept>
#include <string>

#include "../Math/Vector.hpp"
#include "../Utils/IOUtils.hpp"

template<
    typename Traits = std::char_traits<char>,
    typename Allocator = std::allocator<char>
>
class WavefrontParser
{
    friend class WavefrontParserException;
public:
    using istream = std::basic_istream<char, Traits>;
protected:
    using string = std::basic_string<char, Traits, Allocator>;

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
protected:
    explicit WavefrontParser(istream& sourceStream);
protected:
    auto ForEachCommand(std::function<bool(string)>) -> void;
public:
    virtual ~WavefrontParser() = default;
protected:
    std::size_t currentLine = 1;
    typename Traits::pos_type lineStartPos;
    istream& sourceStream;
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

    template<typename Traits, typename Allocator>
    inline explicit WavefrontParserException(
            const WavefrontParser<Traits, Allocator>& parser,
            const std::string& message)
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
auto WavefrontParser<Traits, Allocator>::ForEachCommand(
        std::function<bool(string)> parse) -> void
{
    string command{};

    while(!sourceStream.eof())
    {
        lineStartPos = sourceStream.tellg();
        ioutils::ReadWhile(sourceStream, { Space, Tab });
        ioutils::ReadUntil(sourceStream, SpaceOrLineEnd, command);

        if (command.size() > 0 && command[0] != u8'#')
        {
            const bool parsed = parse(command);
            if (!parsed) {
                std::cout << "Unknown Wavefront command at line "
                    << currentLine << ", column "
                    << sourceStream.tellg() - lineStartPos
                    << ", skipping.\n";
            }
        }

        ioutils::ReadUntil(sourceStream, LineEnd);
        ioutils::ReadWhile(sourceStream, LineEnd);

        command.clear();
        currentLine += 1;
    }
}

#endif /* end of include guard: AMN_WAVEFRONT_PARSER__HPP */
