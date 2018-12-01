//@	{"targets":[{"name":"type_set.test","type":"application","autorun":1}]}

#include "type_set.hpp"

#include <cassert>

using TypeSetTest = Analib::TypeSet<int, float, double>;

static_assert(TypeSetTest::size() == 3);
static_assert(TypeSetTest::getTypeIndex<int>() == 0);
static_assert(TypeSetTest::getTypeIndex<float>() == 1);
static_assert(TypeSetTest::getTypeIndex<double>() == 2);

static_assert(TypeSetTest::getTypeIndex<Analib::GetType<0, TypeSetTest>::type>() == 0);
static_assert(TypeSetTest::getTypeIndex<Analib::GetType<1, TypeSetTest>::type>() == 1);
static_assert(TypeSetTest::getTypeIndex<Analib::GetType<2, TypeSetTest>::type>() == 2);

static_assert(std::is_same_v<Analib::GetType<TypeSetTest::getTypeIndex<int>(), TypeSetTest>::type, int>);
static_assert(std::is_same_v<Analib::GetType<TypeSetTest::getTypeIndex<float>(), TypeSetTest>::type, float>);
static_assert(std::is_same_v<Analib::GetType<TypeSetTest::getTypeIndex<double>(), TypeSetTest>::type, double>);

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
