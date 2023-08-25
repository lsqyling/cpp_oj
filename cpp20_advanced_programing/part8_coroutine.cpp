#include <co_context/all.hpp>
#include <iostream>


co_context::generator<int> gen_iota(int x)
{
    while (true)
        co_yield x++;
}

int main()
{
    using namespace std::views;

    for (int x: gen_iota(1) | drop(5) | take(3))
    {
        std::cout << x << " ";
    }
    // 输出 6 7 8

    return 0;
}