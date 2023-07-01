#pragma once

namespace func_traits
{
	template <bool C>
	struct bool_constant
	{
		static constexpr bool value = C;
	};

	struct true_type : bool_constant<true> {};
	struct false_type : bool_constant<false> {};

	template <typename>
	struct is_function : false_type {};

	template <typename F, typename... Args>
	struct is_function<F(Args...)> : true_type {};
	
	template <typename F, typename... Args>
	struct is_function<F(*)(Args...)> : true_type {};

	template <typename F, typename C, typename... Args>
	struct is_function<F(C::*)(Args...)> : true_type {};

	template <typename F, typename C, typename... Args>
	struct is_function<F(C::*)(Args...) const> : true_type {};

	template <typename F>
	inline constexpr bool is_function_v = is_function<F>::value;
}