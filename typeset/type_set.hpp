//@	{"targets":[{"name":"type_set.hpp","type":"include"}]}

#ifndef ANALIB_TYPESET_HPP
#define ANALIB_TYPESET_HPP

#include <cstddef>
#include <type_traits>
#include <array>

namespace Analib
	{
	template<class T>
	struct Empty{};

	namespace ts_detail
		{
		template<class TypeSet, class T, size_t index>
		struct TypeIndex;

		template<class Callback, class Type>
		[[nodiscard]] auto option(Callback& callback)
			{return callback(Empty<Type>{});}

		template<class Callback>
		[[nodiscard]] auto unknown_type(Callback& callback)
			{return callback();}

		template<class Callback>
		using Option = std::decay_t<decltype(unknown_type<Callback>)>;

		template<class Callback, size_t N>
		using VtableEntries = std::array<Option<Callback>, N>;

		template<class Callback, class TypeSet>
		constexpr VtableEntries<Callback, TypeSet::size()> createVtable();
		}

	template<class ... Types>
	struct TypeSet
		{
		[[nodiscard]] static constexpr size_t size()
			{return sizeof...(Types);}

		template<class T>
		[[nodiscard]] static constexpr auto getTypeIndex()
			{
			constexpr auto index = ts_detail::TypeIndex<TypeSet, T, size()>::value;
			static_assert(index != size(), "Type not found");
			return index;
			}

		template<class Callback>
		[[nodiscard]] static inline auto select(size_t type_index, Callback&& cb);
		};

	template<size_t N, class T>
	struct GetType;

	template<size_t N, class Head, class ... Tail>
	struct GetType<N, TypeSet<Head, Tail...>>:GetType<N-1, TypeSet<Tail...>>
		{};

	template<class Head, class ... Tail>
	struct GetType<0, TypeSet<Head, Tail...>>
		{using type = Head;};


	namespace ts_detail
		{
		template<class TypeSet, class T, size_t index = TypeSet::size()>
		struct TypeIndex
			{
			static constexpr auto value = std::is_same_v<typename GetType<index - 1, TypeSet>::type, T> ?
				index - 1 : TypeIndex<TypeSet, T, index - 1>::value;
			};
		template<class TypeSet, class T>
		struct TypeIndex<TypeSet, T, 0>
			{static constexpr auto value = TypeSet::size(); };



		template<class Callback, class TypeSet, size_t N=TypeSet::size()>
		struct BuildVtable
			{
			using CurrentType = typename GetType<N - 1, TypeSet>::type;
			static constexpr auto vt_size = TypeSet::size();
			static constexpr void setCallback(VtableEntries<Callback, vt_size>& vt)
				{
				vt[N - 1] = option<Callback, CurrentType>;
				return BuildVtable<Callback, TypeSet, N - 1>::setCallback(vt);
				}
			};

		template<class Callback, class TypeSet>
		struct BuildVtable<Callback, TypeSet, 0>
			{
			static constexpr auto vt_size = TypeSet::size();
			static constexpr void setCallback(VtableEntries<Callback, vt_size>&)
				{ }
			};

		template<class Callback, class TypeSet>
		constexpr VtableEntries<Callback, TypeSet::size()> createVtable()
			{
			VtableEntries<Callback, TypeSet::size()> ret{};
			BuildVtable<Callback, TypeSet>::setCallback(ret);
			return ret;
			}
		template<class Callback, class TypeSet>
		constexpr auto Vtable = createVtable<Callback, TypeSet>();
		}

	template<class ... Types>
	template<class Callback>
	inline auto TypeSet<Types...>::select(size_t type_index, Callback&& cb)
		{
		if(__builtin_expect(type_index < size(), 1))
			{return ts_detail::Vtable<Callback, TypeSet<Types...>>[type_index](cb);}
		return cb();
		}
	}
#endif