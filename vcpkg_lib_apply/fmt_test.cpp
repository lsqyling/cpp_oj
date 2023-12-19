#include <fmt/core.h>
#include <string>















int main()
{
    std::string world = fmt::format("Hello {}", "world!");
    fmt::print("{}", world);
    return 0;
}