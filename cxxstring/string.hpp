//@	{
//@	"targets":[{"name":"string.hpp","type":"include"}]
//@	}

#ifndef STRING_HPP
#define STRING_HPP

#include <vector>
#include <memory>

template<template<class> class BaseContainer, class ... ContainerArgs>
class String:private BaseContainer<char, ContainerArgs...>
	{
	public:
		using Base = BaseContainer<char, ContainerArgs...>;
		using std::vector<char>::begin;
		using std::vector<char>::end;
		using std::vector<char>::capacity;
		using std::vector<char>::size;
		using std::vector<char>::reserve;
		using std::vector<char>::data;

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
			{return m_data;}

	private:
		std::vector<char> m_data;
	};


template<template<class> class BaseContainer, class ... ContainerArgs>
template<class InputIterator>
String<BaseContainer, ContainerArgs...>& String<BaseContainer, ContainerArgs...>::append(InputIterator begin, InputIterator end)
	{
	m_data.reserve(size() + std::distance(begin, end));
	while(begin!=end)
		{
		m_data.emplace_back(std::forward<decltype(*begin)>(*begin));
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

#endif
