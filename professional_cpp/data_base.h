#ifndef PROFESSIONAL_CPP_DATA_BASE_H
#define PROFESSIONAL_CPP_DATA_BASE_H

#include <vector>
#include "employee.h"



namespace records {
const int FirstEmployeeNumber = 1000;

class data_base
{
public:
    employee &add_employee(const std::string &first_name, const std::string &last_name);
    employee &get_employee(int employee_number);
    employee &get_employee(const std::string &first_name, const std::string &last_name);

    void display_all() const;
    void display_current() const;
    void display_former() const;



private:
    std::vector<employee> employees_;
    int next_employee_number_{FirstEmployeeNumber};

};
}

#endif
