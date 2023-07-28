#include "airline_ticket.h"


AirlineTicket::AirlineTicket() :
passenger_name_("Unkown Passenger"),
number_of_miles_(0),
has_elites_super_rewards_status_(0)
{

}

AirlineTicket::~AirlineTicket() = default;

double AirlineTicket::calc_price_in_dollars()
{
    if (has_elites_super_rewards_status())
        return 0;
    else
        return get_number_of_miles() * 0.1;
}

std::string AirlineTicket::get_passenger_name()
{
    return passenger_name_;
}

void AirlineTicket::set_passenger_name(std::string name)
{
    passenger_name_ = name;


}

int AirlineTicket::get_number_of_miles()
{
    return number_of_miles_;
}

void AirlineTicket::set_number_of_miles(int miles)
{
    number_of_miles_ = miles;

}

bool AirlineTicket::has_elites_super_rewards_status()
{
    return has_elites_super_rewards_status_;
}

void AirlineTicket::set_has_elites_super_rewards_status(bool flag)
{
    has_elites_super_rewards_status_ = flag;
}
