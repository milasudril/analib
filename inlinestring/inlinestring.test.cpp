//@	{
//@	"targets":[{"name":"inlinestring.test","type":"application","autorun":1}]
//@	}

#undef NDEBUG

#include "inlinestring.hpp"

#include <cassert>

int main()
	{
	Analib::InlineString shortString{"1"};
	static_assert(alignof(shortString) == sizeof(intptr_t), "Bad alignment");
	static_assert(alignof(shortString) == shortString.alignment(), "Bad alignment");
	static_assert(shortString.capacity() == 2, "Bad capacity");
	static_assert(sizeof(shortString) >= shortString.capacity(), "Inline storage");
	static_assert(static_cast<void*>(shortString.begin()) == static_cast<void*>(&shortString), "Inline storage");
	static_assert(shortString.size() == shortString.end() - shortString.begin(), "Bad capacity");


	Analib::InlineString longString{"01234567"};
	static_assert(longString.alignment() == 16, "Bad alignment for large string");

	Analib::InlineString a{"Hello"};
	Analib::InlineString b{"Foo\0\0"};
	Analib::InlineString c{"Hello"};

	assert( a > b);
	assert( b < a);
	assert( a >= b);
	assert( b <= a);
	assert( a!= b);
	assert( a == c);

	auto copy = a;
	assert( copy == c);
	}
