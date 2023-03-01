#pragma once

#include <tuple>
#include <cstdint>

namespace function_traits
{
	template <typename Func>
	struct function_traits : public function_traits<decltype(&std::decay<Func>::type::operator())>
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
			using type = std::tuple_element<i, std::tuple<Args...>>::type;
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
}