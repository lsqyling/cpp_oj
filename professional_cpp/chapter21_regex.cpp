#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <fstream>
#include "format.h"

namespace regex {

void test_wstring()
{
    std::string str{"北京欢迎你！"};
    const char8_t *s1 = u8"Raw UTF-8 encoded string literal";
    const wchar_t *s2 = L"Raw wide string literal";
    const char16_t *s3 = u"Raw char16_t string literal";
    const char32_t *s4 = U"Raw char32_t string literal";

    std::u8string ss1{s1};
    std::wstring ss2{s2};
    std::u16string ss3{s3};
    std::u32string ss4{s4};

    std::wcout << "ss2 = " << ss2 << "\n";
}


void test_locale()
{
    std::stringstream stream;
    stream << 32767;
    std::cout << stream.str() << std::endl;
}

void test_date_regex_expression()
{
    std::regex r{R"(\d{4}/(?:0?[1-9]|1[0-2])/(?:0?[1-9]|[1-2][0-9]|3[0-1]))"};
    std::ifstream ifs{R"(D:\dev\workspace\clion\oj\professional_cpp\regex.data)"};
    std::cout << "Automatically loaded the data of regex.data using file stream:" << std::endl;
    while (true)
    {
        std::string str;
        if (!std::getline(ifs, str))
            break;
        if (std::regex_match(str, r))
            std::cout << "Valid date." << "\n";
        else
            std::cout << "Invalid date!" << "\n";
    }
}

void test_date_regex_match()
{
    std::regex r{R"((\d{4})/(0?[1-9]|1[0-2])/(0?[1-9]|[1-2][0-9]|3[0-1]))"};
    std::ifstream ifs{R"(D:\dev\workspace\clion\oj\professional_cpp\regex.data)"};
    std::cout << "Automatically loaded the data of regex.data using file stream:" << std::endl;
    while (true)
    {
        std::string str;
        if (!std::getline(ifs, str))
            break;
        if (std::smatch m; std::regex_match(str, m, r))
        {
            int year = std::stoi(m[1]);
            int month = std::stoi(m[2]);
            int day = std::stoi(m[3]);
            std::cout << std::format("Valid date: Year={}, month={}, day={}",
                                     year, month, day)
                      << "\n";
        }
        else
        {
            std::cout << "Invalid date!" << "\n";
        }
    }
}

void test_regex_search()
{
    std::ifstream ifs{R"(D:\dev\workspace\clion\oj\professional_cpp\include\fmt\core.h)"};
    std::regex r{R"(//\s*(.+)$)"};
    std::cout << "Automatically loaded the data of core.h using file stream:" << std::endl;
    bool flag = true;
    while (true)
    {
        std::string str;
        if (!std::getline(ifs, str))
            break;
        if (std::smatch m; std::regex_search(str, m, r))
        {
            std::cout << std::format("Found comment: '{}'", m[1].str()) << "\n";
            flag = false;
        }
    }
    if (flag)
        std::cout << "No comment found!" << std::endl;
}

void test_regex_iterator()
{
    std::ifstream ifs{R"(D:\dev\workspace\clion\oj\professional_cpp\regex.data)"};
    std::regex r{R"(\w+)"};
    std::cout << "Automatically loaded the data of regex.data using file stream:" << std::endl;

    while (true)
    {
        std::string str;
        if (!std::getline(ifs, str))
            break;

        const std::sregex_iterator end;
        for (std::sregex_iterator it{std::cbegin(str), std::cend(str), r};
        it != end; ++it)
        {
            std::cout << std::format("\"{}\"", it->str()) << " ";
        }
    }
}

void test_regex_token_iterator()
{
    std::ifstream ifs{R"(D:\dev\workspace\clion\oj\professional_cpp\regex.data)"};
    std::cout << "Automatically loaded the data of regex.data using file stream:" << std::endl;
    std::regex r{R"(\w+)"};
    while (true)
    {
        std::string str;
        if (!std::getline(ifs, str))
            break;

        const std::sregex_token_iterator end;
        for (std::sregex_token_iterator it{std::cbegin(str), std::cend(str), r};
             it != end; ++it)
        {
            std::cout << std::format("\"{}\"", it->str()) << " ";
        }
    }
}

void test_string_split()
{
    std::ifstream ifs{R"(D:\dev\workspace\clion\oj\professional_cpp\regex.data)"};
    std::cout << "Automatically loaded the data of regex.data using file stream:" << std::endl;
    std::regex r{R"(\s*[,;]\s*)"};
    while (true)
    {
        std::string str;
        if (!std::getline(ifs, str))
            break;
        const std::sregex_token_iterator end;
        auto it = std::sregex_token_iterator(std::cbegin(str), std::cend(str), r, -1);
        for (; it != end; ++it)
        {
            std::cout << std::format("\"{}\"", it->str()) << " ";
        }
    }
}

void test_regex_replace()
{
    std::ifstream ifs{R"(D:\dev\workspace\clion\oj\professional_cpp\test.html)"};
    std::cout << "Automatically loaded the data of test.html using file stream:" << std::endl;
    std::regex r{R"(<h1>(.*)</h1><p>(.*)</p>)"};

    while (true)
    {
        std::string str;
        if (!std::getline(ifs, str))
            break;

        const std::string replace_str{"H1 = $1 and P = $2"};
        std::string result = std::regex_replace(str, r, replace_str);

        std::cout << std::format("Original string: '{}'", str) << "\n";
        std::cout << std::format("New string     : '{}'", result) << "\n";
    }
}

void test_regex_replace_nocopy()
{
    std::ifstream ifs{R"(D:\dev\workspace\clion\oj\professional_cpp\test.html)"};
    std::cout << "Automatically loaded the data of test.html using file stream:" << std::endl;
    std::regex r{R"((\w+))"};
    const std::string replace_str{"$1\n"};

    while (true)
    {
        std::string str;
        if (!std::getline(ifs, str))
            break;

        std::cout << std::regex_replace(str, r, replace_str, std::regex_constants::format_no_copy)
                  << "\n";
    }
}
}

namespace regex::exercise {
void test_fact()
{
    std::locale loc_str{"POSIX"};
    auto c = std::use_facet<std::numpunct<char>>(loc_str).decimal_point();
    std::cout << "decimal point: " << c << std::endl;
}

void test_valid_phonenumber()
{
    std::ifstream ifs{R"(D:\dev\workspace\clion\oj\professional_cpp\phone_number.data)"};
    std::cout << "Automatically loaded the data of phone number using file stream." << std::endl;

    std::regex r{R"(([0-9]{3})-([0-9]{3})-([0-9]{4}))"};
    while (true)
    {
        std::string str;
        if (!std::getline(ifs, str))
            break;
        if (std::smatch m; std::regex_match(str, m, r))
        {

            std::cout << std::format("matched: {}-{}-{}\n", m[1].str(), m[2].str(), m[3].str())
                      << "\n";
        }
    }
}






}





int main(int argc, char *argv[])
{
    regex::test_wstring();
    regex::test_locale();
    regex::test_date_regex_expression();
    regex::test_date_regex_match();
    regex::test_regex_search();
    regex::test_regex_iterator();
    regex::test_regex_token_iterator();
    regex::test_string_split();

    std::cout << "------------" << std::endl;
    std::cout << "------------" << std::endl;
    std::cout << "------------" << std::endl;
    regex::test_regex_replace();
    regex::test_regex_replace_nocopy();

    regex::exercise::test_fact();
    regex::exercise::test_valid_phonenumber();

    return 0;
}