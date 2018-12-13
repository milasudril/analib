//@	{"targets":[{"name":"type_set.test","type":"application","autorun":1}]}

#include "type_set.hpp"

#include <cassert>
#include <vector>

using EmptyType = std::vector<Analib::Empty<int>>;

static_assert(Analib::ts_detail::IsContainerOfEmpty<EmptyType>::value);

using TypeSetTest = Analib::TypeSet<int, float, EmptyType, double>;

static_assert(TypeSetTest::size() == 4);

static_assert(TypeSetTest::getTypeIndex<int>() == 0);
static_assert(TypeSetTest::getTypeIndex<float>() == 1);
static_assert(TypeSetTest::getTypeIndex<EmptyType>() == 2);
static_assert(TypeSetTest::getTypeIndex<double>() == 3);

static_assert(TypeSetTest::getTypeIndex<Analib::GetType<0, TypeSetTest>::type>() == 0);
static_assert(TypeSetTest::getTypeIndex<Analib::GetType<1, TypeSetTest>::type>() == 1);
static_assert(TypeSetTest::getTypeIndex<Analib::GetType<2, TypeSetTest>::type>() == 2);
static_assert(TypeSetTest::getTypeIndex<Analib::GetType<3, TypeSetTest>::type>() == 3);

static_assert(std::is_same_v<Analib::GetType<TypeSetTest::getTypeIndex<int>(), TypeSetTest>::type, int>);
static_assert(std::is_same_v<Analib::GetType<TypeSetTest::getTypeIndex<float>(), TypeSetTest>::type, float>);
static_assert(std::is_same_v<Analib::GetType<TypeSetTest::getTypeIndex<double>(), TypeSetTest>::type, double>);
static_assert(std::is_same_v<Analib::GetType<TypeSetTest::getTypeIndex<EmptyType>(), TypeSetTest>::type, EmptyType>);

struct SelectTest
	{
	size_t operator()(Analib::Empty<int>)
		{return 0;}

	size_t operator()(Analib::Empty<float>)
		{return 1;}

	size_t operator()(Analib::Empty<double>)
		{return 3;}

	size_t operator()()
		{return 10;}
	};

int main()
	{
	for(size_t k=0; k<TypeSetTest::size(); ++k)
		{assert(TypeSetTest::select(k, SelectTest{}) == (k != 2? k: 10));}


	assert(TypeSetTest::select(3974028375u, SelectTest{}) == 10);

	return 0;
	}
