#include <compare>
#include <limits>
#include "format.h"

namespace pro::test::hello {

void foo()
{
    std::cout << "Hello namespace " << std::endl;
    std::cout << std::format("There are {} ways I love you.", 219) << std::endl;
}

void print_number_limits()
{
    std::cout << "int:\n";
    std::cout << std::format("Max int value: {}\n", std::numeric_limits<int>::max());
    std::cout << std::format("Min int value: {}\n", std::numeric_limits<int>::min());
    std::cout << std::format("Lowest int value: {}\n", std::numeric_limits<int>::lowest());
    std::cout << "\ndouble:\n";

    std::cout << std::format("Max double value: {}\n", std::numeric_limits<double>::max());
    std::cout << std::format("Min double value: {}\n", std::numeric_limits<double>::min());
    std::cout << std::format("Lowest double value: {}\n", std::numeric_limits<double>::lowest());
}

void three_ways_compare_operator()
{
    int i = 11;
    std::strong_ordering result{i <=> 0};

    if (result == std::strong_ordering::less)
        std::cout << "less" << std::endl;
    if (result == std::strong_ordering::greater)
        std::cout << "greater" << std::endl;
    if (result == std::strong_ordering::equal)
        std::cout << "equal" << std::endl;

    if (std::is_lt(result))
        std::cout << "less" << std::endl;
    if (std::is_gt(result))
        std::cout << "greater" << std::endl;
    if (std::is_eq(result))
        std::cout << "equal" << std::endl;
}

int add_numbers(int a, int b)
{
    std::cout << std::format("Entering function {}", __func__) << std::endl;
    return a + b;
}

void test_add_two_numbers()
{
    int x{add_numbers(2, 3)};
    std::cout << std::format("x = {}\n", x) << std::endl;
}

struct employee
{
    char first_initial;
    char last_initial;
    int number;
    int salary;
};

void init_employee()
{
    employee an_employee{
        .first_initial = 'J',
        .last_initial = 'D',
        .number = 42,
        .salary = 8500
    };


    std::cout << std::format("an employee first: {}, last: {}, number: {}, salary: {}.\n",
            an_employee.first_initial, an_employee.last_initial, an_employee.number, an_employee.salary);
}





}










int main(int argc, char *argv[])
{
    pro::test::hello::foo();
    pro::test::hello::print_number_limits();
    pro::test::hello::three_ways_compare_operator();
    pro::test::hello::test_add_two_numbers();
    pro::test::hello::init_employee();
    return 0;
}
