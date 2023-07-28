#include "employee.h"
#include "format.h"

namespace records {

employee::employee(const std::string &first_name, const std::string &last_name):
first_name_(first_name), last_name_(last_name)
{

}

void employee::promote(int raise_amount)
{
    set_salary(get_salary() + raise_amount);

}

void employee::demote(int demerit_amount)
{
    set_salary(get_salary() - demerit_amount);

}

void employee::hire()
{
    hired_ = true;
}

void employee::fire()
{
    hired_ = false;

}

void employee::display() const
{
    std::cout << std::format("Employee: {}, {}", get_last_name(), get_first_name()) << "\n"
    << "-----------------------------" << "\n"
    << (is_hired() ? "Current Employee" : "Former Employee") << "\n"
    << std::format("Employee Number: {}", get_employee_number()) << "\n"
    << std::format("Salary: ${}", get_salary()) << std::endl;
}

const std::string &employee::get_first_name() const
{
    return first_name_;
}

void employee::set_first_name(const std::string &first_name)
{
    first_name_ = first_name;

}

const std::string &employee::get_last_name() const
{
    return last_name_;
}

void employee::set_last_name(const std::string &last_name)
{
    last_name_ = last_name;

}

int employee::get_employee_number() const
{
    return employee_number_;
}

void employee::set_employee_number(int employee_number)
{
    employee_number_ = employee_number;

}

int employee::get_salary() const
{
    return salary_;
}

void employee::set_salary(int salary)
{
    salary_ = salary;

}

bool employee::is_hired() const
{
    return hired_;
}

void employee::set_hired(bool hired)
{
    hired_ = hired;
}

}