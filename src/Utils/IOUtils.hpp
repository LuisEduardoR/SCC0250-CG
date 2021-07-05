#ifndef AMN_IOUTILS_HPP
#define AMN_IOUTILS_HPP

#include <algorithm>
#include <initializer_list>
#include <ios>
#include <iostream>
#include <memory>
#include <string>

namespace ioutils
{

template<typename Container>
auto Contains(const Container& container, typename Container::value_type value) -> bool
{
	return std::find(container.begin(), container.end(), value) != container.end();
}

template<
	typename CharT,
	typename Traits = std::char_traits<CharT>,
	typename Container = std::initializer_list<typename Traits::int_type>
>
auto ReadWhile(
	std::basic_istream<CharT, Traits>& stream,
	 Container allowed)
{
	static_assert(std::is_same_v<typename Container::value_type, typename Traits::int_type>);

	for (auto c = stream.peek(); c != Traits::eof() && Contains(allowed, c); c = stream.peek())
	{
		stream.seekg(1, std::ios_base::cur);
	}
}

template<
	typename CharT,
	typename Traits = std::char_traits<CharT>,
	typename Container = std::initializer_list<typename Traits::int_type>,
	typename Allocator = std::allocator<CharT>
>
auto ReadWhile(
	std::basic_istream<CharT, Traits>& stream,
	Container allowed,
	std::basic_string<CharT, Traits, Allocator>& output)
{
	static_assert(std::is_same_v<typename Container::value_type, typename Traits::int_type>);

	for (auto c = stream.peek(); c != Traits::eof() && Contains(allowed, c); c = stream.peek())
	{
		output.push_back(Traits::to_char_type(c));
		stream.seekg(1, std::ios_base::cur);
	}
}

template<
	typename CharT,
	typename Traits = std::char_traits<CharT>,
	typename Container = std::initializer_list<typename Traits::int_type>,
	typename Allocator = std::allocator<CharT>
>
auto ReadUntil(
	std::basic_istream<CharT, Traits>& stream,
	Container delimiters)
{
	static_assert(std::is_same_v<typename Container::value_type, typename Traits::int_type>);

	for (auto c = stream.peek(); c != Traits::eof() && !Contains(delimiters, c);
			c = stream.peek())
	{
		stream.seekg(1, std::ios_base::cur);
	}
}

template<
	typename CharT,
	typename Traits = std::char_traits<CharT>,
	typename Container = std::initializer_list<typename Traits::int_type>,
	typename Allocator = std::allocator<CharT>
>
auto ReadUntil(
	std::basic_istream<CharT, Traits>& stream,
	Container delimiters,
	std::basic_string<CharT, Traits, Allocator>& output)
{
	static_assert(std::is_same_v<typename Container::value_type, typename Traits::int_type>);

	for (auto c = stream.peek(); c != Traits::eof() && !Contains(delimiters, c);
			c = stream.peek())
	{
		output.push_back(Traits::to_char_type(c));
		stream.seekg(1, std::ios_base::cur);
	}
}

} /* amn::ioutils */ 

#endif /* end of include guard: AMN_IOUTILS_HPP */
