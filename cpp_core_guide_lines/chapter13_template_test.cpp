#include <vector>
#include <iostream>
#include <algorithm>
#include <concepts>
namespace t40 {
class sum_me
{
public:
    void operator()(int x)
    {
        sum += x;
    }

    int get_sum() const { return sum; }

private:
    int sum{0};
};


void test()
{
    std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sum_me me = std::for_each(nums.begin(), nums.end(), sum_me());
    std::cout << '\n';
    std::cout << "Sum of intVec = " << me.get_sum() << '\n';
    std::cout << '\n';
}
}

namespace t44 {
template<typename T>
void show_me_func(const T &t)
{
    std::cout << t << '\n';
}

template<typename T>
struct show_me_t
{
    show_me_t(const T &t)
    {
        std::cout << t << '\n';
    }
};

void test()
{
    show_me_func(5);
    show_me_func(5.5);
    show_me_t a(5.5);
    show_me_t b(5);
}
}

namespace t46 {

void test()
{
    std::cout << std::boolalpha << '\n';

    std::cout << "std::is_default_constructible_v<int&>: " << std::is_default_constructible_v<int&> << '\n';
    std::cout << "std::is_copy_constructible_v<int&>: " << std::is_copy_constructible_v<int&> << '\n';
    std::cout << "std::is_copy_assignable_v<int&>: " << std::is_copy_assignable_v<int&> << '\n';
    std::cout << "std::is_move_constructible_v<int&>: " << std::is_move_constructible_v<int&> << '\n';
    std::cout << "std::is_move_assignable_v<int&>: " << std::is_move_assignable_v<int&> << '\n';
    std::cout << "std::is_destructible_v<int&>: " << std::is_destructible_v<int&> << '\n';
    std::cout << "std::is_swappable_v<int&>: " << std::is_swappable_v<int&> << '\n';

    std::cout << '\n';
}

}
namespace t48 {
template<typename T,
        typename std::enable_if_t<std::is_integral_v<T>, T> = 0>
T gcd_not_enough_good(T a, T b)
{
    if (b == 0) return a;
    return gcd_not_enough_good(b, a % b);
}

template<std::integral T>
T gcd(T a, T b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}


void test()
{
    std::cout << '\n';

    std::cout << "gcd_not_enough_good(100, 10) = " << gcd_not_enough_good(100, 10) << '\n';
//    std::cout << "gcd_not_enough_good(3.5, 4.0) = " << gcd_not_enough_good(3.5, 4.0) << '\n';

    std::cout << "gcd(100, 10) = " << gcd(100, 10) << '\n';
//    std::cout << "gcd(3.5, 4.0) = " << gcd(3.5, 4.0) << '\n';

    std::cout << '\n';
}
}




















int main()
{
    t40::test();
    t44::test();
    t46::test();
    t48::test();
    return 0;
}