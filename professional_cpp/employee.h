#ifndef PROFESSIONAL_CPP_EMPLOYEE_H
#define PROFESSIONAL_CPP_EMPLOYEE_H

#include <string>

namespace records {

static const int DefaultStartingSalary = 30'000;
const int DefaultRaiseAndDemeritAmount = 1'000;


class employee
{
public:
    employee(const std::string &first_name, const std::string &last_name);
    void promote(int raise_amount = DefaultRaiseAndDemeritAmount);
    void demote(int demerit_amount = DefaultRaiseAndDemeritAmount);
    void hire();
    void fire();
    void display() const;

    const std::string &get_first_name() const;

    void set_first_name(const std::string &first_name);

    const std::string &get_last_name() const;

    void set_last_name(const std::string &last_name);

    int get_employee_number() const;

    void set_employee_number(int employee_number);

    int get_salary() const;

    void set_salary(int salary);

    bool is_hired() const;

    void set_hired(bool hired);


private:
    std::string first_name_;
    std::string last_name_;
    int employee_number_{-1};
    int salary_{DefaultStartingSalary};
    bool hired_{false};
};


}





#endif