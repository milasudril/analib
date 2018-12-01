//@	{"targets":[{"name": "constexpr_cast.hpp", "type":"include"}]}

#ifndef ANALIB_CONSTEXPR_CAST_HPP
#define ANALIB_CONSTEXPR_CAST_HPP

#include <limits>

namespace Analib
	{
	template<class To, class From, From n>
	struct ConstexprCast
		{
		//FIXME: Is this check always correct? -Wsign-compare
		static_assert(n>=std::numeric_limits<To>::min() && n<=std::numeric_limits<To>::max()
			, "n is outside allowed range");
		static constexpr auto value = static_cast<To>(n);
		};
	}

#endif
