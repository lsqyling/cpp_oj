#include <vector>
#include <iostream>
#include <ranges>
#include <map>

namespace rg {
using std::cout;
using std::endl;
namespace views = std::views;
namespace ranges = std::ranges;

template<ranges::input_range R>
auto sum(R &&r)
{
    ranges::range_value_t<R> ret{};
    for (auto e : r) ret += e;
    return ret;
}

void test_ranges()
{
    auto res = std::views::iota(1)
               | views::transform([](auto n) { return n * n; })
               | views::filter([](auto n) { return n % 2 == 1; })
               | views::take_while([](auto n) { return n < 10000; });
    cout << sum(res) << endl;
}

static_assert(ranges::range<std::vector<int>>);
static_assert(ranges::range<int[10]>);
static_assert(ranges::range<std::array<int, 10>>);

void test_view_factory()
{
    auto v = ranges::empty_view<int>{};
    static_assert(ranges::empty_view<int>::empty());

    auto v1 = views::single(6);
    cout << *v1.data() << endl;

    for (auto e : ranges::iota_view{0, 5})
        cout << e << ' ';
    cout << endl;
    for (auto e : views::iota(0, 5))
        cout << e << ' ';
    cout << endl;
}

void test_range_adapter()
{
    std::vector vi{0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    auto even = [](auto i) { return i % 2 == 0; };
    auto square = [](auto i) { return i * i; };
    auto res = vi
               | views::filter(even)
               | views::transform(square)
               | views::take(6)
               | views::take_while([](auto i) { return i <= 100;})
               | views::drop(1)
               | views::drop_while([](auto i) { return i <= 16; })
               | views::reverse;
    for (const auto &i: res)
    {
        cout << i << ' ';
    }
    cout << endl;
    std::vector<std::string_view> ss{"hello", "", "world", "!"};
    auto greeting = ss | views::join;
    for (const auto &item: greeting)
    {
        cout << item << " ";
    }
    cout << endl;
    std::string_view str{"the quick brown fox"};
    auto sentence = str | views::split(' ');
    for (auto word: sentence)
    {
        for (auto c : word) cout << c;
        cout << "*";
    }
    cout << endl;

    std::map<std::string_view, long> figures{
            {"Lovelace", 1815}, {"Turing", 1912},
            {"Babbage", 1791}, {"Hamilton", 1936}
    };

    auto names = figures | views::elements<0>;
    for (const auto &name : names)
        cout << name << " ";
    cout << endl;
    auto birth_days = figures | views::elements<1>;
    for (const auto &d : birth_days)
        cout << d << " ";
    cout << endl;
}

}



int main()
{

    rg::test_ranges();
    rg::test_view_factory();
    rg::test_range_adapter();



    return 0;
}