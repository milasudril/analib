//@	{
//@	"targets":[{"name":"string.hpp","type":"include"}]
//@	}

#ifndef ANALIB_STRING_HPP
#define ANALIB_STRING_HPP

#include <memory>

namespace Analib
	{
	template<class CharT, class Container>
	class String : private Container
		{
		public:
			using Container::begin;
			using Container::end;
			using Container::capacity;
			using Container::size;
			using Container::reserve;
			using Container::data;

			explicit String(CharT const* cstr)
				{append(cstr);}

			template<class InputIterator>
			explicit String(InputIterator begin, InputIterator end)
				{append(begin, end);}

			String& append(const CharT* cstr);
			String& append(String const& str)
				{return append(str.begin(), str.end());}

			template<class InputIterator>
			String& append(InputIterator begin, InputIterator end);

			String& append(CharT ch)
				{
				Container::push_back(ch);
				return *this;
				}
		};


	template<class CharT, class Container>
	template<class InputIterator>
	String<CharT, Container>& String<CharT,Container>::append(InputIterator begin, InputIterator end)
		{
		reserve(size() + std::distance(begin, end));
		while(begin!=end)
			{
			emplace_back(std::forward<decltype(*begin)>(*begin));
			++begin;
			}
		return *this;
		}


	template<class CharT, class Container>
	std::unique_ptr<char const[]> make_cstr(String<CharT, Container> const& str);

	}

#endif
