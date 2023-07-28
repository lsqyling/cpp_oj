#include <string>
class AirlineTicket
{
public:
    AirlineTicket();
    ~AirlineTicket();

    double calc_price_in_dollars();
    std::string get_passenger_name();
    void set_passenger_name(std::string name);
    int get_number_of_miles();
    void set_number_of_miles(int miles);

    bool has_elites_super_rewards_status();
    void set_has_elites_super_rewards_status(bool flag);

private:
    std::string passenger_name_;
    int number_of_miles_;
    bool has_elites_super_rewards_status_;
};
