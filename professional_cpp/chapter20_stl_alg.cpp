#include <algorithm>
#include <vector>
#include <numeric>
#include <span>
#include <cmath>
#include <iostream>


namespace alg {

double arithmetic_mean(std::vector<int> &nums)
{
    double sum = std::accumulate(std::cbegin(nums), std::cend(nums), 0.0);
    return sum / static_cast<double>(nums.size());
}


double geometric_mean(std::span<const int> values)
{
    double mult = std::accumulate(values.begin(), values.end(), 1, [](int a, int b) { return a * b;});
    return std::pow(mult, 1.0/static_cast<double>(values.size()));
}

auto is_perfect_score = [tally = 0](int i) mutable{
    std::cout << ++tally << std::endl;
    return i >= 100;
};


void test_mean()
{
    std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::cout << "arithmetic_mean = " << arithmetic_mean(nums) << "\n";
    std::cout << "geometric_mean = " << geometric_mean(nums) << "\n";

    std::vector<int> scores{67, 98, 30, 60, 100};
    is_perfect_score(0);
    if (auto it = std::find_if(std::cbegin(scores), std::cend(scores), is_perfect_score);
            it != std::cend(scores))
    {
        std::cout << "the perfect score is " << *it << std::endl;
    }
    else
        std::cout << "Not of the score is perfect!" << std::endl;
}

void test_search_find()
{
    std::vector<int> nums{5, 6, 9, 8, 8, 3};
    auto beg = std::cbegin(nums);
    auto end = std::cend(nums);
    auto it = std::find_if_not(beg, end, [](int i) { return i < 8; });
    if (it != end)
        std::cout << "First element not < 8 is " << *it << std::endl;
    it = std::adjacent_find(beg, end);
    if (it != end)
        std::cout << "Found tow consecutive equal elements with value " << *it << std::endl;

    std::vector targets{8, 9};
    it = std::find_first_of(beg, end, std::cbegin(targets), std::cend(targets));
    if (it != end)
        std::cout << "Found one of 8 or 9: " << *it << std::endl;
    std::vector sub{8, 3};
    it = std::search(beg, end, std::cbegin(sub), std::cend(sub));
    if (it != end)
        std::cout << "Found subsequence {8, 3}" << std::endl;
    else
        std::cout << "Unable to find subsequence {8, 3}" << std::endl;
}

























}

















int main()
{
    alg::test_mean();
    alg::test_search_find();
    return 0;
}