//@	{"targets":[{"name":"type_set.test","type":"application","autorun":1}]}

#include "type_set.hpp"

#include <cassert>

using TypeSetTest = Analib::TypeSet<int, float, double>;

static_assert(TypeSetTest::size() == 3);
static_assert(TypeSetTest::getTypeIndex<int>()==0);
static_assert(TypeSetTest::getTypeIndex<float>()==1);
static_assert(TypeSetTest::getTypeIndex<double>()==2);

struct SelectTest
	{
	size_t operator()(Analib::Empty<int>)
		{return 0;}

	size_t operator()(Analib::Empty<float>)
		{return 1;}

	size_t operator()(Analib::Empty<double>)
		{return 2;}

	size_t operator()()
		{return 3;}
	};

int main()
	{
	for(size_t k=0; k<TypeSetTest::size(); ++k)
		{assert(TypeSetTest::select(k, SelectTest{}) == k);}


	assert(TypeSetTest::select(3974028375u, SelectTest{}) == 3);

	return 0;
	}
