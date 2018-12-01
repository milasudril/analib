//@	{"targets":[{"name": "constexpr_cast.test", "type":"application","autorun":1}]}

#include "constexpr_cast.hpp"

#include <cstdint>

constexpr auto good_1 = Analib::ConstexprCast<int8_t, uint8_t, 127>::value;
//constexpr auto fail = Analib::ConstexprCast<int8_t, uint8_t, 128>::value;
constexpr auto good_2 = Analib::ConstexprCast<uint8_t, int8_t, 0>::value;
//constexpr auto fail = Analib::ConstexprCast<uint8_t, int8_t, -128>::value;
constexpr auto good_3 = Analib::ConstexprCast<uint8_t, uint16_t, 255>::value;
//constexpr auto fail = Analib::ConstexprCast<uint8_t, uint16_t, 256>::value;

int main()
	{
	return 0;
	}
