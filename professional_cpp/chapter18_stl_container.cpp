#include <numeric>
#include <vector>
#include <iostream>
#include <span>
#include <map>
#include "format.h"
#include "bank.h"

namespace container {
void test_double_vector()
{
    double max = -std::numeric_limits<double>::infinity();
    std::vector<double> list(10);
    for (int i = 0; i < 10; ++i)
    {
        std::cin >> list[i];
        if (list[i] > max)
            max = list[i];
    }
    max /= 100.0;
    for (auto &item: list)
    {
        item /= max;
        std::cout << item << " ";
    }
}

template<typename T>
void print(std::span<T> views)
{
    for (const auto &item: views)
    {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void test_print()
{
    std::vector<int> nums{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    print<int>(nums);

    std::span my_view{nums};
    print<int>(my_view.subspan(0));
    print<int>({nums.data() + 3, 3});


    std::array<int, 5> arr{5, 4, 3, 2, 1};
    print<int>(arr);

    int carr[]{9, 8, 7, 6, 5};
    print<int>(carr);
    print<int>({carr + 2, 3});
}

void test_map()
{
    std::map<std::string, int> data_map{{"zhangsan", 20},
                                        {"lisi", 23},
                                        {"wangwu", 25},
                                        {"shiqing", 36}};

    for (auto &[key, value]: data_map)
    {
        std::cout << key << " " << value << "\n";
    }

    std::cout << std::format("data_map contains shiqing? {}", data_map.contains("shiqing")) << std::endl;

}


void test_db()
{
    bank_db db;
    db.add_account({100, "Nicholas Solter"});
    db.add_account({200, "Scott Kleper"});

    try
    {
        auto &acc = db.find_account(100);
        std::cout << "Found account 100" << std::endl;
        acc.set_client_name("Nicholas A Solter");

        auto &acct2 = db.find_account("Scott Kleper");
        std::cout << "Found account of Scott Kleper" << std::endl;
        auto &acct3 = db.find_account(1000);
    } catch (const std::out_of_range &e)
    {
        std::cout << "Unable to find account: " << e.what() << std::endl;
    }
}
}


int main()
{
//    container::test_double_vector();
    container::test_print();
    container::test_map();
    container::test_db();



    return 0;
}