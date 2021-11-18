#include <iostream>


template <typename>
struct is_function : std::false_type
{};

template <typename f, typename ... types >
struct is_function< f(types...) >: std::true_type
{};

template <typename f, typename ... types >
struct is_function< f(types...) const > : std::true_type
{};

template <typename f, typename ... types >
struct is_function< f(types...)& > : std::true_type
{};

template <typename f, typename ... types >
struct is_function< f(types...) const & > : std::true_type
{};

template <typename f>
inline const bool is_function_v = is_function <f> ::value;

int main()
{
    bool ans = is_function_v <int(double, char) const >;
    std::cout << std::boolalpha << ans;
}