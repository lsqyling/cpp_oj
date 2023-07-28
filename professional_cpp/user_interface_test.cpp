#include "format.h"
#include "employee.h"
#include "data_base.h"


using namespace records;

int display_menu()
{
    std::cout << "Employee Database\n"
    << "-----------------\n"
    << "1) Hire a new employee\n"
    << "2) Fire an employee\n"
    << "3) Promote an employee\n"
    << "4) List all employees\n"
    << "5) List all current employees\n"
    << "6) List all former employees\n"
    << "0) Quit\n"
    << "--> ";
    int selection;
    std::cin >> selection;
    return selection;
}

void do_hire(data_base &db)
{
    std::string first, last;
    std::cout << "First name? ";
    std::cin >> first;
    std::cout << "Last name? ";
    std::cin >> last;
    auto &an = db.add_employee(first, last);
    std::cout << std::format("Hired employee {} {} with employee number {}.",
            an.get_first_name(), an.get_last_name(), an.get_employee_number())
            << std::endl;
}

void do_fire(data_base &db)
{
    int number;
    std::cout << "Employee number? ";
    std::cin >> number;

    try
    {
        auto &an = db.get_employee(number);
        an.fire();
        std::cout << std::format("Employee {} terminated.", number) << std::endl;
    } catch (const std::logic_error &e)
    {
        std::cerr << std::format("Unable to terminate employee: {}", e.what()) << std::endl;
    }
}

void do_promote(data_base &db)
{
    int number;
    std::cout << "Employee number? ";
    std::cin >> number;

    int raise_amount;
    std::cout << "How much of a raise? ";
    std::cin >> raise_amount;

    try
    {
        auto &an = db.get_employee(number);
        an.promote(raise_amount);
    } catch (const std::logic_error &e)
    {
        std::cerr << std::format("Unable to promote employee: {}", e.what()) << std::endl;
    }
}


int main(int argc, char *argv[])
{
    data_base db;
    bool done = false;
    while (!done)
    {
        int selection = display_menu();
        switch (selection)
        {
            case 0:
                done = true;
                break;
            case 1:
                do_hire(db);
                break;
            case 2:
                do_fire(db);
                break;
            case 3:
                do_promote(db);
                break;
            case 4:
                db.display_all();
                break;
            case 5:
                db.display_current();
                break;
            case 6:
                db.display_former();
                break;
            default:
                std::cerr << "Unknown command." << std::endl;
                break;
        }
    }
    return 0;
}


