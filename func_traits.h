#pragma once

#include "is_function.h"

namespace func_traits
{
	using size_t = decltype(sizeof(nullptr));

	namespace detail
	{
		template <size_t I, typename... Args>
		struct nth_type
		{
			static_assert(I < sizeof...(Args), "Invalid access to non existent argument!");

			using type = nth_type<I - 1, Args...>::type;
		};

		template <size_t I, typename F, typename... Args>
		struct nth_type<I, F, Args...> : nth_type<I - 1, Args...> { };

		template <typename F, typename... Args>
		struct nth_type<0, F, Args...>
		{
			using type = F;
		};
	}

	template <bool isPointer, bool isConst, typename R, typename... Args>
	struct function
	{
		using return_type = R;

		static constexpr size_t arity = sizeof...(Args);

		static constexpr bool is_pointer = isPointer;
		static constexpr bool is_const = isConst;

		template <size_t i>
		struct arg
		{
			using type = typename detail::nth_type<i, Args...>::type;
		};
	};

	template <typename R>
	struct func_traits : public func_traits<decltype(&R::operator())> { };

	template <typename R, typename... Args>
	struct func_traits<R(Args...)> : public function<false, false, R, Args...> { };

	template <typename R, typename... Args>
	struct func_traits<R(*)(Args...)> : public function<true, false, R, Args...> { };

	template <typename R, typename C, typename... Args>
	struct func_traits<R(C::*)(Args...)> : public function<false, true, R, Args...> { };

	template <typename R, typename C, typename... Args>
	struct func_traits<R(C::*)(Args...) const> : public function<true, true, R, Args...> { };
}