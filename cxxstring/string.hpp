//@	{
//@	"targets":[{"name":"string.hpp","type":"include"}]
//@	}

#ifndef ANALIB_STRING_HPP
#define ANALIB_STRING_HPP

#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <type_traits>

namespace Analib
	{
	/**A class that can contain a string.
	 *
	 * \param CharT The type used to represent **code units**. A CharT is assumed to support the same expressions as
	 *              the CharT parameter for std::basic_string.
	 *
	 * \param Container The container type used to store the code units. If c is a Container, then the following
	 *                  expressions must be valid:
	 *
	 *                      c.begin()           returns an iterator to the beginning of the container
	 *                      c.cbegin()          returns a const_iterator to the beginning of the container
	 *                      c.end()             returns an iterator to the end of the container
	 *                      c.cend()            returns a const_iterator to the end of the container
	 *                      c.size()            returns the number of code units in the container
	 *                      c.push_back(CharT)  appends one CharT to the end of the container
	 *
	 *                  In addition to that, c *may* also support
	 *
	 *                      c.data()
	 *
	 *                   which should return a CharT const*.
	 */
	template<class CharT, class Container>
	class BasicString : private Container
		{
		public:
			using value_type = CharT;

			using Container::begin;
			using Container::end;
			using Container::cbegin;
			using Container::cend;
			using Container::size;

			BasicString(char)=delete;
			BasicString(short)=delete;
			BasicString(int)=delete;
			BasicString(long)=delete;
			BasicString(long long)=delete;

			BasicString(unsigned char)=delete;
			BasicString(unsigned short)=delete;
			BasicString(unsigned int)=delete;
			BasicString(unsigned long)=delete;
			BasicString(unsigned long long)=delete;

			BasicString() = default;

			/**A BasicString can be constructed from a C-style string.
			 */
			explicit BasicString(CharT const* cstr)
				{append(cstr);}

			/** A BasicString can be constructed from two InputIterator.
			 */
			template<class InputIterator>
			explicit BasicString(InputIterator begin, InputIterator end)
				{append(begin, end);}

			/**Appends cstr to the BasicString, and returns *this.
			 *
			 * \note cstr must point to a valid C-style string.
			 */
			BasicString& append(CharT const* cstr);

			/**Appends str to *this and returns *this.
			 */
			BasicString& append(BasicString const& str)
				{return append(str.begin(), str.end());}


			/**Appends the range [begin, end) to *this and returns *this.
			 */
			template<class InputIterator>
			BasicString& append(InputIterator begin, InputIterator end);

			/**Appends ch to *this and returns *this
			 */
			BasicString& append(CharT ch)
				{
				this->push_back(ch);
				return *this;
				}

			/**Compares *this to other and returns true iff they are equal, as defined by Container.
			*/
			bool operator==(BasicString const& other) const
				{return *this == static_cast<Container const&>(other);}


#if __cplusplus >= 201703L
			/**Returns a std::basic_string_view representing the string.
			 *
			 * \note This method is available iff Container supports the `data` method and the compiler supports C++17.
			 */
			auto string_view() const
				{return std::basic_string_view<CharT>{Container::data(), size()};}
#endif

			auto data()
				{return Container::data();}

			auto data() const
				{return Container::data();}

			void resize(size_t size)
				{Container::resize(size);}
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

	/**Checks that str is a valid C-style string. A valid C-style string must not contain any nul char.
	*
	* \returns True iff str is a valid C-style string.
	*/
	template<class CharT, class Container>
	bool valid_cstr(BasicString<CharT, Container> const& str)
		{return std::find(str.begin(), str.end(), static_cast<CharT>(0)) == str.end();}



	/**Converts str to a C-style string, by copying its content followed by a nul char to a new array of CharT. The
	* behaviour is undefined if str cannot be represented as a C-style string. Use valid_cstr to check that str can
	* be represented as a C-style string.
	*/
	template<class CharT, class Container>
	std::unique_ptr<CharT const[]> make_cstr(BasicString<CharT, Container> const& str)
		{
		assert(valid_cstr(str));
		auto ret = std::make_unique<CharT []>(str.size() + 1);
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
		return ch_in==static_cast<CharT>(0) && pos_a!=a.end();
		}

	template<class CharT, class Container>
	bool operator==(BasicString<CharT, Container> const& a, CharT const* cstr)
		{return !(a != cstr);}

	template<class CharT, class Container>
	bool operator==(CharT const* cstr, BasicString<CharT, Container> const& a)
		{return a==cstr;}

	template<class CharT, class Container>
	bool operator!=(CharT const* cstr, BasicString<CharT, Container> const& a)
		{return a!=cstr;}

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

	/**A string type without SSO (Small string optimization). Use this if you cannot take advantage of SSO, or the SSO
	 * version is too large (on 64-bit libstdc++ it is 8 byte larger).
	 */
	using StringNoSso = BasicString<char, std::vector<char>>;

	/**The default string. Basically, it uses std::string as Container.
	 */
	using DefaultString = BasicString<char, std::string>;
	}

#endif
