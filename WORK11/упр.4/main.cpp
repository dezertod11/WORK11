#include <iostream>

template < bool C, typename True_Type>
struct enable_if
{
    using type = True_Type;
};

template < typename True_Type >
struct enable_if < false, True_Type >
{};

template < bool C, typename TT >
using enable_if_t = typename enable_if < C, TT >::type;

int main() {}