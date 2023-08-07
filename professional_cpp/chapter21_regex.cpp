#include <string>
#include <iostream>
#include <format>
#include <sstream>

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

void test_regex_expression()
{











}







}












int main()
{
    regex::test_wstring();
    regex::test_locale();
    return 0;
}