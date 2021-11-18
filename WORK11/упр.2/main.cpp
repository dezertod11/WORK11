#include <iostream>

template < typename T >
struct remove_const
{
    using type = T;
};

template < typename T >
struct remove_const < const T >
{
    using type = T;
};

template <typename T>
using remove_const_t = typename remove_const <const T> ::type;

template < typename T >
struct add_const
{
    using type = const T;
};

template <typename T>
using add_const_t = typename add_const <T> ::type;

int main()
{
    std::cout << std::boolalpha << std::is_same <int, add_const_t<int>>::value << std::endl;
    std::cout << std::boolalpha << std::is_same <const int, remove_const_t<const int>>::value;
    return EXIT_SUCCESS;
}