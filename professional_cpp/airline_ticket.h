#include <string>
class AirlineTicket
{
public:
    AirlineTicket();
    ~AirlineTicket();

    double calc_price_in_dollars() const;
    std::string get_passenger_name() const;
    void set_passenger_name(std::string name);
    int get_number_of_miles() const;
    void set_number_of_miles(int miles);

    bool has_elites_super_rewards_status() const;
    void set_has_elites_super_rewards_status(bool flag);

private:
    std::string passenger_name_;
    int number_of_miles_;
    bool has_elites_super_rewards_status_;
};
