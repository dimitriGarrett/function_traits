# function_traits

A simple utility to get compile time information about functions, and lambdas. Everything is compile time, so performance isn't an issue.

It works pretty simply for functions, it just takes the signature and extracts the information from it.

The only extra part for lambdas is it gets the operator(), and inherits from the func_trait for function pointers.

# Warning

This does not work for generic lambdas (i.e. where auto is used as an input type)
