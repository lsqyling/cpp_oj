#include <stdexcept>
#include "data_base.h"



namespace records {
employee &data_base::add_employee(const std::string &first_name, const std::string &last_name)
{
    employee an(first_name, last_name);
    an.set_employee_number(next_employee_number_++);
    an.hire();
    employees_.push_back(an);
    return employees_.back();
}

employee &data_base::get_employee(int employee_number)
{
    for (auto &an : employees_)
    {
        if (an.get_employee_number() == employee_number)
            return an;
    }
    throw std::logic_error("No employee found.");
}

employee &data_base::get_employee(const std::string &first_name, const std::string &last_name)
{
    for (auto &an : employees_)
    {
        if (an.get_first_name() == first_name && an.get_last_name() == last_name)
            return an;
    }
    throw std::logic_error("No employee found.");
}

void data_base::display_all() const
{
    for (const auto &an : employees_)
    {
        an.display();
    }

}

void data_base::display_current() const
{
    for (const auto &an : employees_)
    {
        if (an.is_hired())
            an.display();
    }

}

void data_base::display_former() const
{
    for (const auto &an : employees_)
    {
        if (!an.is_hired())
            an.display();
    }

}


}