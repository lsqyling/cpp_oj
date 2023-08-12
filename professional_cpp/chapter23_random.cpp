#include <random>
#include <iostream>
#include <ctime>
#include <functional>
#include <map>
#include <fstream>

namespace rm {

void test_random_engine()
{
    std::random_device rd;
    std::cout << "Entropy: " << rd.entropy() << "\n"
              << "Min value: " << std::random_device::min() << "\n"
              << "Max value: " << std::random_device::max() << "\n"
              << "Random value: " << rd() << std::endl;

    std::random_device seeder;
    const auto seed = seeder.entropy() != 0 ? seeder() : std::time(nullptr);
    std::mt19937 engine(seed);
    std::uniform_int_distribution<int> u{1, 99};
    std::cout << u(engine) << std::endl;


    auto generator = std::bind(u, engine);
    std::vector<int> values(10);
    std::generate(values.begin(), values.end(), generator);
    for (const auto &item: values)
    {
        std::cout << item << " ";
    }

}


void test_uniform_random_distribution()
{
    const int Start = 1;
    const int End = 99;
    const int Iterations = 1'000'000;
    std::random_device seeder;
    const auto seed = seeder.entropy() != 0 ? seeder() : std::time(nullptr);
    std::mt19937 engine(seed);


    std::uniform_int_distribution<int> u{Start, End};
    auto generator = std::bind(u, engine);

    std::map<int, int> histogram;
    for (int i = 0; i < Iterations; ++i)
    {
        ++histogram[generator()];
    }

    std::ofstream ofs{R"(D:\dev\workspace\clion\oj\professional_cpp\res.csv)"};
    for (int i = Start; i <= End; ++i)
    {
        ofs << i << "," << histogram[i] << "\n";
    }
}

void test_normal_random_distribution()
{
    const int Start = 1;
    const int End = 99;
    const int Iterations = 1'000'000;
    std::random_device seeder;
    const auto seed = seeder.entropy() != 0 ? seeder() : std::time(nullptr);
    std::mt19937 engine(seed);


    std::normal_distribution<double> u{50, 10};

    auto generator = std::bind(u, engine);

    std::map<int, int> histogram;
    for (int i = 0; i < Iterations; ++i)
    {
        ++histogram[static_cast<int>(generator())];
    }

    std::ofstream ofs{R"(D:\dev\workspace\clion\oj\professional_cpp\res_normal.csv)"};
    for (int i = Start; i <= End; ++i)
    {
        ofs << i << "," << histogram[i] << "\n";
    }
}






}







int main()
{
    rm::test_random_engine();
    rm::test_uniform_random_distribution();
    rm::test_normal_random_distribution();



    return 0;
}