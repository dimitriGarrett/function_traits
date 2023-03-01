#pragma once

#include <tuple>
#include <cstdint>

namespace function_traits
{
	template <typename Func>
	struct func_traits : public func_traits<decltype(&std::decay_t<Func>::operator())>
	{
	};

	template <typename R, typename... Args>
	struct func_base
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
	struct func_traits<Func(*)(Args...)> : public func_base<Func, Args...>
	{
	};

	template <typename Func, typename... Args>
	struct func_traits<Func(Args...)> : public func_base<Func, Args...>
	{
	};

	template <typename Class, typename Func, typename... Args>
	struct func_traits<Func(Class::*)(Args...)> : public func_base<Func, Args...>
	{
		using class_type = Class;
	};

	template <typename Class, typename Func, typename... Args>
	struct func_traits<Func(Class::*)(Args...) const> : public func_base<Func, Args...>
	{
		using class_type = Class;
	};
}