#include <string>
#include <string_view>
#include "format.h"

namespace str {

std::string_view extract_extensions(std::string_view filename)
{
    return filename.substr(filename.rfind('.'));
}

void test_extract_extensions()
{
    std::string filename{R"(c:\temp\my file.txt)"};
    std::cout << std::format("C++ string: {}", extract_extensions(filename)) << std::endl;

    const char *cstr = R"(c:\tmp\my file.txt)";
    std::cout << std::format("C string: {}", extract_extensions(cstr)) << std::endl;

    std::cout << std::format("Literal: {}", extract_extensions(R"(c:\temp\my file.txt)")) << std::endl;
}


void test_format()
{
    int i = 42;

    std::cout << "Width: ------------" << std::endl;
    std::cout << std::format("|{:5}|", i) << std::endl;
    std::cout << std::format("|{:{}}|", i, 7) << std::endl;

    std::cout << "Align: ------------" << std::endl;
    std::cout << std::format("|{:07}|", i) << std::endl;
    std::cout << std::format("|{:<7}|", i) << std::endl;
    std::cout << std::format("|{:0>7}|", i) << std::endl;
    std::cout << std::format("|{:0^7}|", i) << std::endl;

    std::cout << "Sign: ------------" << std::endl;
    std::cout << std::format("|{:+05}|", -i) << std::endl;
    std::cout << std::format("|{:<+05}|", i) << std::endl;
    std::cout << std::format("|{:>+05}|", -i) << std::endl;
    std::cout << std::format("|{:0^ 5}|", i) << std::endl;

    std::cout << "Type: ------------" << std::endl;
    std::cout << std::format("|{:10d}|", i) << std::endl;
    std::cout << std::format("|{:10b}|", i) << std::endl;
    std::cout << std::format("|{:#10b}|", i) << std::endl;
    std::cout << std::format("|{:#10B}|", i) << std::endl;
    std::cout << std::format("|{:10B}|", i) << std::endl;
    std::cout << std::format("|{:10x}|", i) << std::endl;
    std::cout << std::format("|{:10X}|", i) << std::endl;
    std::cout << std::format("|{:#10X}|", i) << std::endl;
    std::cout << std::format("|{:#10x}|", i) << std::endl;
    std::cout << std::format("|{:#10o}|", i) << std::endl;
    std::cout << std::format("|{:10o}|", i) << std::endl;

    double d = 3.1415 / 2.3;
    std::cout << "Precision: ------------" << std::endl;
    std::cout << std::format("|{:12g}|", d) << std::endl;
    std::cout << std::format("|{:12.2}|", d) << std::endl;
    std::cout << std::format("|{:.2f}|", d) << std::endl;
    std::cout << std::format("|{:.6f}|", d) << std::endl;
    std::cout << std::format("|{:.8f}|", d) << std::endl;
    std::cout << std::format("|{:.2e}|", d) << std::endl;
    std::cout << std::format("|{:6.2E}|", d) << std::endl;

    std::cout << "0: ------------" << std::endl;
    std::cout << std::format("|{:06d}|", i) << std::endl;
    std::cout << std::format("|{:+06d}|", i) << std::endl;
    std::cout << std::format("|{:+06d}|", -i) << std::endl;
    std::cout << std::format("|{:+06x}|", i) << std::endl;
    std::cout << std::format("|{:+#06X}|", -i) << std::endl;
}
}



int main()
{
    str::test_extract_extensions();
    str::test_format();


    return 0;
}