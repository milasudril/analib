//@	{"targets":[{"type":"application","name":"string.test","autorun":1}]}

#include "string.hpp"

#include <cassert>
#include <cstring>

static char const teststr[]="Hello, World";

template<class TestType>
void stringTest()
	{
	TestType stringFromCstr{"Hello, World"};

	static_assert(sizeof(teststr)!=sizeof(void*));
	TestType stringFromRange{teststr, teststr + sizeof(teststr) - 1};  // Must remove nul char here!

	assert(stringFromRange == stringFromCstr);
	assert(stringFromRange == "Hello, World");
	assert("Hello, World" == stringFromRange);

	auto copy = stringFromRange;
	assert(stringFromRange.append("More text") != copy);
	assert(stringFromRange != "Hello, World");

	assert(copy.append(stringFromCstr)=="Hello WorldHello, World");

	assert(strcmp(make_cstr(TestType{teststr}).get(), teststr) == 0);

	copy.append('\0');
	assert(make_cstr(copy) == nullptr);
	}

int main()
	{
	stringTest<Analib::DefaultString>();
	stringTest<Analib::StringNoSso>();
	return 0;
	}
