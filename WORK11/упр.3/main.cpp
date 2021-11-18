#include <iostream>

//checking if smth is a function (from the first exercise)
template <typename>
struct is_function : std::false_type
{};

template <typename f, typename ... types >
struct is_function< f(types...) > : std::true_type
{};

template <typename f, typename ... types >
struct is_function< f(types...) const > : std::true_type
{};

template <typename f, typename ... types >
struct is_function< f(types...)& > : std::true_type
{};

template <typename f, typename ... types >
struct is_function< f(types...) const& > : std::true_type
{};

template <typename f>
inline const bool is_function_v = is_function <f> ::value;

//if_then_else

template < bool c, typename true_type, typename false_type >
struct if_then_else
{
    using type = true_type;
};

template < typename true_type, typename false_type >
struct if_then_else < false, true_type, false_type >
{
    using type = false_type;
};

template < bool c, typename tt, typename ft >
using if_then_else_t = typename if_then_else < c, tt, ft >::type;

//checking if smth is an array

template<typename t>
struct is_array : std::false_type {};

template<typename t>
struct is_array<t[]> : std::true_type {};

template<typename t, std::size_t n>
struct is_array<t[n]> : std::true_type {};

template <typename t >
inline const bool is_array_v = is_array<t>::value;

//removing brackets

template<typename t>
struct remove_brackets
{
    using type = t;
};

template<typename t>
struct remove_brackets<t[]>
{
    using type = t;
};

template<typename t, std::size_t n>
struct remove_brackets<t[n]>
{
    using type = t;
};

template<typename t>
using remove_brackets_t = typename remove_brackets<t>::type;

//finally, decay

template <typename t>
struct decay
{
    using rt = std::remove_reference_t<t>;
    using type = if_then_else_t< is_function_v<rt>, rt*,
            if_then_else_t<is_array_v<rt>, remove_brackets_t<rt>*, rt>>;
};

template <typename t>
using decay_t = typename decay<t>::type;

int main()
{
    std::cout << std::boolalpha << std::is_same<int*, decay_t<int []>>::value;
}