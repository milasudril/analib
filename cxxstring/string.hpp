//@	{
//@	"targets":[{"name":"string.hpp","type":"include"}]
//@	}

#ifndef ANNALIB_STRING_HPP
#define ANALIB_STRING_HPP

#include <memory>

namespace Analib
	{
	template<template<class> class BaseContainer, class ... ContainerArgs>
	class String:private BaseContainer<char, ContainerArgs...>
		{
		public:
			using Base = BaseContainer<char, ContainerArgs...>;
			using Base::begin;
			using Base::end;
			using Base::capacity;
			using Base::size;
			using Base::reserve;
			using Base::data;

			explicit String(char const* cstr)
				{append(cstr);}

			template<class InputIterator>
			explicit String(InputIterator begin, InputIterator end)
				{append(begin, end);}

			String& append(const char* cstr);
			String& append(String const& str)
				{return append(str.begin(), str.end());}

			template<class InputIterator>
			String& append(InputIterator begin, InputIterator end);

			auto const& representation() const noexcept
				{return static_cast<Base const&>(*this);}
		};


	template<template<class> class BaseContainer, class ... ContainerArgs>
	template<class InputIterator>
	String<BaseContainer, ContainerArgs...>& String<BaseContainer, ContainerArgs...>::append(InputIterator begin, InputIterator end)
		{
		reserve(size() + std::distance(begin, end));
		while(begin!=end)
			{
			emplace_back(std::forward<decltype(*begin)>(*begin));
			++begin;
			}
		return *this;
		}


	template<template<class> class BaseContainer, class ... ContainerArgs>
	std::unique_ptr<char const[]> make_cstr(String<BaseContainer, ContainerArgs...> const& str);

	template<template<class> class BaseContainer, class ... ContainerArgs>
	inline bool operator==(String<BaseContainer, ContainerArgs...> const& a, String<BaseContainer, ContainerArgs...> const& b)
		{return a.representation() == b.representation();}

	template<template<class> class BaseContainer, class ... ContainerArgs>
	inline bool operator!=(String<BaseContainer, ContainerArgs...> const& a, String<BaseContainer, ContainerArgs...> const& b)
		{return a.representation() != b.representation();}


	template<template<class> class BaseContainer, class ... ContainerArgs>
	bool operator!=(String<BaseContainer, ContainerArgs...> const& a, char const* b) noexcept;

	template<template<class> class BaseContainer, class ... ContainerArgs>
	inline bool operator!=(char const* a, String<BaseContainer, ContainerArgs...> const& b)
		{return b != a;}

	template<template<class> class BaseContainer, class ... ContainerArgs>
	inline bool operator==(String<BaseContainer, ContainerArgs...> const& a, char const* b)
		{return !(a != b);}

	template<template<class> class BaseContainer, class ... ContainerArgs>
	inline bool operator==(char const* a, String<BaseContainer, ContainerArgs...> const& b)
		{return b==a;}

	}

#endif
