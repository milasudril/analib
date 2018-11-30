Name: typeset
Purpose: To provide a way to store a list of types, and to create a mapping between types and integers
Description: The typeset module contains a class template

	namespace Analib
		{
		template<class ... Types>
		struct TypeSet;
		}

and some helper types. For a full desciription of that class, see `type_set.hpp`.
