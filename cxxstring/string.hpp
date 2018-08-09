//@	{
//@	"targets":[{"name":"string.hpp","type":"include"}]
//@	}

#ifndef ANALIB_STRING_HPP
#define ANALIB_STRING_HPP

#include <memory>
#include <vector>
#include <string>
#include <algorithm>

namespace Analib
	{
	template<class CharT, class Container>
	class BasicString : private Container
		{
		public:
			using Container::begin;
			using Container::end;
			using Container::cbegin;
			using Container::cend;
			using Container::size;

			explicit BasicString(CharT const* cstr)
				{append(cstr);}

			template<class InputIterator>
			explicit BasicString(InputIterator begin, InputIterator end)
				{append(begin, end);}

			BasicString& append(CharT const* cstr);

			BasicString& append(BasicString const& str)
				{return append(str.begin(), str.end());}

			template<class InputIterator>
			BasicString& append(InputIterator begin, InputIterator end);

			BasicString& append(CharT ch)
				{
				this->push_back(ch);
				return *this;
				}

			bool operator==(BasicString const& other) const
				{return *this == static_cast<Container const&>(other);}


#if __cplusplus >= 201703L
			auto string_view() const
				{return std::basic_string_view<CharT>{Container::data(), size()};}
#endif
		};


	template<class CharT, class Container>
	template<class InputIterator>
	BasicString<CharT, Container>& BasicString<CharT,Container>::append(InputIterator begin, InputIterator end)
		{
		while(begin!=end)
			{
			append(*begin);
			++begin;
			}
		return *this;
		}


	template<class CharT, class Container>
	std::unique_ptr<char const[]> make_cstr(BasicString<CharT, Container> const& str)
		{
		if(std::find(str.begin(), str.end(), static_cast<CharT>(0)) != str.end())
			{return nullptr;}
		auto ret = std::make_unique<char []>(str.size() + 1);
		std::copy(str.begin(), str.end(), ret.get());
		*(ret.get() + str.size()) = static_cast<CharT>(0);
		return std::move(ret);
		}

	template<class CharT, class Container>
	inline bool operator!=(BasicString<CharT, Container> const& a, BasicString<CharT, Container> const& b)
		{return !(a == b);}

	template<class CharT, class Container>
	bool operator!=(BasicString<CharT, Container> const& a, CharT const* cstr)
		{
		auto ch_in = *cstr;
		auto pos_a = a.begin();
		while(ch_in!=static_cast<CharT>(0) && pos_a!=a.end())
			{
			if(ch_in != *pos_a)
				{return true;}
			++cstr;
			++pos_a;
			ch_in=*cstr;
			}
		return false;
		}

	template<class CharT, class Container>
	bool operator==(BasicString<CharT, Container> const& a, CharT const* cstr)
		{return !(a != cstr);}

	template<class CharT, class Container>
	bool operator==(CharT const* cstr, BasicString<CharT, Container> const& a)
		{return cstr == a;}

	template<class CharT, class Container>
	bool operator!=(CharT const* cstr, BasicString<CharT, Container> const& a)
		{return cstr != a;}

#if __cplusplus>=201703L
	template<class CharT, class Container>
	inline bool operator==(BasicString<CharT, Container> const& a, std::basic_string_view<CharT> b)
		{return a.string_view() == b;}

	template<class CharT, class Container>
	inline bool operator!=(BasicString<CharT, Container> const& a, std::basic_string_view<CharT> b)
		{return !(a.string_view() == b);}

	template<class CharT, class Container>
	inline bool operator==(std::basic_string_view<CharT> a, BasicString<CharT, Container> const& b)
		{return a==b.string_view();}

	template<class CharT, class Container>
	inline bool operator!=(std::basic_string_view<CharT> a, BasicString<CharT, Container> const& b)
		{return !(a==b);}
#endif

	template<class CharT, class Container>
	BasicString<CharT, Container>& BasicString<CharT, Container>::append(const CharT* cstr)
		{
		auto ch_in = *cstr;
		while(ch_in!=static_cast<CharT>(0))
			{
			append(ch_in);
			++cstr;
			ch_in=*cstr;
			}
		return *this;
		}

	using StringNoSso = BasicString<char, std::vector<char>>;
	using DefaultString = BasicString<char, std::string>;
	}

#endif
