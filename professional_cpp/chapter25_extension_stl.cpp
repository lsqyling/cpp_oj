#include <algorithm>
#include <vector>
#include <iostream>

namespace ds {
using std::cout;
using std::endl;

void test_ds()
{
    std::vector<int> vi{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> result(10);
    auto end = std::copy_if(vi.begin(), vi.end(), result.begin(),
                            [](auto i) { return i % 2 == 0; });

    std::for_each(result.begin(), end,
                  [](auto i) { cout << i << " "; });
    cout << endl;
}


template<typename InputIterator, typename OutputIterator, typename Predicate>
OutputIterator find_all(InputIterator first, InputIterator last,
                        OutputIterator dest, Predicate pred)
{
    while (first != last)
    {
        if (pred(*first))
        {
            *dest = *first;
            ++dest;
        }
        ++first;
    }
    return dest;
}

void test_find_all()
{
    std::vector<int> vi{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> result(10);
    auto end = find_all(vi.begin(), vi.end(), result.begin(),
                            [](auto i) { return i % 2 == 0; });

    std::for_each(result.begin(), end,
                  [](auto i) { cout << i << " "; });

    cout << endl;
}






}


int main()
{
    ds::test_ds();
    ds::test_find_all();



    return 0;
}