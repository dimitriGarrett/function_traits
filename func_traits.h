#pragma once

#include <tuple>
#include <cstdint>

namespace function_traits
{
	template <typename Func>
	struct function_traits : public function_traits<decltype(&std::decay_t<Func>::operator())>
	{
	};

	template <typename R, typename... Args>
	struct function_base
	{
		using return_type = R;

		static constexpr std::size_t arity = sizeof...(Args);

		template <std::size_t i = 0>
		struct arg
		{
			using type = std::tuple_element_t<i, std::tuple<Args...>>;
		};
	};

	template <typename Func, typename... Args>
	struct function_traits<Func(*)(Args...)> : public function_base<Func, Args...>
	{
	};

	template <typename Func, typename... Args>
	struct function_traits<Func(Args...)> : public function_base<Func, Args...>
	{
	};

	template <typename Class, typename Func, typename... Args>
	struct function_traits<Func(Class::*)(Args...)> : public function_base<Func, Args...>
	{
		using class_type = Class;
	};

	template <typename Class, typename Func, typename... Args>
	struct function_traits<Func(Class::*)(Args...) const> : public function_base<Func, Args...>
	{
		using class_type = Class;
	};

	template <bool constant>
	struct bool_constant
	{
		static constexpr bool value = constant;
	};

	struct true_type : bool_constant<true> {};
	struct false_type : bool_constant<false> {};

	template <typename, typename = void>
	struct is_function : false_type {};

	template <typename Func>
	struct is_function<Func, std::void_t<decltype(&std::decay_t<Func>::operator())>> :
		is_function<decltype(&std::decay_t<Func>::operator())> {};

	template <typename R, typename... Args>
	struct is_function<R(Args...)> : true_type {};

	template <typename R, typename... Args>
	struct is_function<R(*)(Args...)> : true_type {};

	template <typename R, typename Class, typename... Args>
	struct is_function<R(Class::*)(Args...)> : true_type {};

	template <typename R, typename Class, typename... Args>
	struct is_function<R(Class::*)(Args...) const> : true_type {};

	template <typename Func>
	static constexpr bool is_function_v = is_function<Func>::value;
}