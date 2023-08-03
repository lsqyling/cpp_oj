#ifndef PROFESSIONAL_CPP_SPREAD_SHEET_H
#define PROFESSIONAL_CPP_SPREAD_SHEET_H
#include <string>
#include <string_view>
class spread_sheet
{


private:
    static std::string double_to_string(double value);
    static double string_to_double(std::string_view value);
};


#endif