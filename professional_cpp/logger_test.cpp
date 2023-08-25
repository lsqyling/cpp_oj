#include "logger.h"
#include "format.h"

void log_some_msg(int id, ts::logger &logger)
{
    for (int i = 0; i < 10; ++i)
    {
        logger.log(std::format("Log entry {} from thread {}", i, id));
    }
}

void test_log_some_msg()
{
    auto &logger = ts::logger::instance();
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i)
    {
        threads.emplace_back(log_some_msg, i, std::ref(logger));
    }

    for (auto &item: threads)
    {
        item.join();
    }
}








int main()
{
    test_log_some_msg();
    auto &logger =  ts::logger::instance();
    std::cout << noexcept(logger.~logger()) << std::endl;
    return 0;
}