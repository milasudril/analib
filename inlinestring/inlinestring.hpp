//@	{
//@	"targets":[{"name":"inlinestring.hpp","type":"include"}]
//@	}

#ifndef ANALIB_INLINESTRING_HPP
#define ANALIB_INLINESTRING_HPP

#include <array>
#include <cstddef>
#include <algorithm>
#include <string>

namespace Analib
	{
#if __cplusplus >= 201703L
	#define INLINESTRING_NODISCARD [[nodiscard]]
#else
	#define INLINESTRING_NODISCARD
#endif
	template<class CharT, size_t N>
	class InlineString
		{
		public:
			InlineString() = default;

			template<size_t M>
			constexpr InlineString(CharT const (&val)[M], std::enable_if_t<(M<N), int> = 0) : m_content{}
				{
				for(size_t k = 0; k<M; ++k)
					{m_content[k] = val[k];}
				}

			constexpr InlineString(CharT const (&val)[N]) : m_content{}
				{
				for(size_t k = 0; k<N; ++k)
					{m_content[k] = val[k];}
				}

			INLINESTRING_NODISCARD constexpr CharT const* begin() const {return m_content.begin();}

			INLINESTRING_NODISCARD constexpr CharT const* end() const {return m_content.end();}

			INLINESTRING_NODISCARD constexpr CharT* begin() {return m_content.begin();}

			INLINESTRING_NODISCARD constexpr CharT* end() {return m_content.end();}

			INLINESTRING_NODISCARD static constexpr auto capacity() {return N;}

			INLINESTRING_NODISCARD static constexpr auto alignment() {return N<=sizeof(intptr_t) ? sizeof(intptr_t) : 16;}

			INLINESTRING_NODISCARD static constexpr auto size() {return N;}

#if __cplusplus >= 201703L
			/**Returns a std::basic_string_view representing the string.
			 */
			INLINESTRING_NODISCARD auto string_view() const
				{return std::basic_string_view<CharT>{begin(), N};}
#endif

		private:
			alignas(alignment()) std::array<CharT, N> m_content;
		};

	template<class CharT, size_t N>
	INLINESTRING_NODISCARD inline bool operator<(InlineString<CharT, N> const& a, InlineString<CharT, N> const& b)
		{return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());}

	template<class CharT, size_t N>
	INLINESTRING_NODISCARD inline bool operator>(InlineString<CharT, N> const& a, InlineString<CharT, N> const& b)
		{return b < a;}

	template<class CharT, size_t N>
	INLINESTRING_NODISCARD inline bool operator==(InlineString<CharT, N> const& a, InlineString<CharT, N> const& b)
		{return std::equal(a.begin(), a.end(), b.begin(), b.end());}

	template<class CharT, size_t N>
	INLINESTRING_NODISCARD inline bool operator>=(InlineString<CharT, N> const& a, InlineString<CharT, N> const& b)
		{return !(a < b);}

	template<class CharT, size_t N>
	INLINESTRING_NODISCARD inline bool operator<=(InlineString<CharT, N> const& a, InlineString<CharT, N> const& b)
		{return !(a > b);}

	template<class CharT, size_t N>
	INLINESTRING_NODISCARD inline bool operator!=(InlineString<CharT, N> const& a, InlineString<CharT, N> const& b)
		{return !(a == b);}
	}

#endif
