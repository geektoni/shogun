/*
* Written (W) 2019 Giovanni De Toni
*/

#ifndef SHOGUN_CLONE_SHOGUN_H
#define SHOGUN_CLONE_SHOGUN_H

#include <type_traits>

namespace shogun {
	namespace clone_utils {

		struct default_copy_ctor
		{
		};

		struct clone_from_value : default_copy_ctor
		{
		};

		struct clone_from_pointer : clone_from_value
		{
		};

		template <class T, std::enable_if_t<std::is_copy_constructible<T>::value>* = nullptr>
		inline T clone_shogun_impl(default_copy_ctor, const T& value)
		{
			return T(value);
		}

		template <class T>
		inline auto clone_shogun_impl(clone_from_value, T& value)
		-> decltype(value.clone())
		{
			return value.clone();
		}

		template <class T>
		inline auto clone_shogun_impl(clone_from_pointer, T* value)
		-> decltype(value->clone())
		{
			return value->clone();
		}

		/**
		 * Method which returns a copy of an object. This is specifically
		 * designed for Shogun since it will call SGOBject's clone() method
		 * when available. If nothing works, then it will use the copy ctor.
		 * @tparam T type
		 * @param value the value we want to clone
		 * @return the cloned value
		 */
		template <class T>
		inline auto clone_shogun(T& value)
		-> decltype(clone_shogun_impl(clone_from_pointer(), value))
		{
			return clone_shogun_impl(clone_from_pointer(), value);
		}

	}
}

#endif //SHOGUN_CLONE_SHOGUN_H
