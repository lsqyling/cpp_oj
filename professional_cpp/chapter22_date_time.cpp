#include <chrono>
#include <ratio>
#include <iostream>
#include <cmath>
#include <regex>
#include "format.h"

namespace dt {
using namespace std::chrono;
using namespace std;

void test_ratio()
{
    using r1 = std::ratio<1, 60>;
    using r2 = std::ratio<1, 90>;

    using result = std::ratio_add<r1, r2>::type;
    using result1 = std::ratio_less<r1, r2>::type;
    std::cout << std::format("{}/{}", result::num, result::den) << std::endl;
    std::cout << std::format("r1 < r2 ? {}", result1::value) << std::endl;

    using result2 = std::ratio_add<std::exa, std::exa>::type;
    std::cout << std::format("{}/{}", result2::num, result2::den) << std::endl;
}

void test_duration()
{

    duration<long, ratio<60>> d1{123};
    cout << d1.count() << std::endl;


//    Define 2 durations
    duration<long, ratio<60>> d3{10};
    duration<long, ratio<1>> d4{14};
    if (d3 > d4)
        cout << "d3 > d4" << endl;
    else
        cout << "d3 <= d4" << endl;
    ++d4;
    d4 *= 2;

    duration<double, ratio<60>> d5{d3 + d4};
    duration<long, ratio<1>> d6{d3 + d4};
    cout << std::format("{} minutes + {} seconds = {} minutes or {} seconds",
                        d3.count(), d4.count(), d5.count(), d6.count())
         << endl;
    duration<long> d7{30};
    duration<double, ratio<60>> d8{d7};
    cout << std::format("{} seconds = {} minutes", d7.count(), d8.count())
         << endl;


    auto t = hours(1) + minutes(23) + seconds(45);
    cout << std::format("{} seconds", t.count()) << endl;

    seconds s{90};
//    minutes m{s}; compiler error
    auto my_duration = 43min;
    auto many_s = duration_cast<duration<long>>(my_duration);
    cout << many_s.count() << endl;
}

//
//void test_clock()
//{
//    auto tp = system_clock::now();
//    auto tt = system_clock::to_time_t(tp);
//    tm *t = localtime(&tt);
//    cout << put_time(t, "%H:%M:%S") << endl;
//
//    stringstream ss;
//    ss << put_time(t, "%H:%M:%S");
//    string str{ss.str()};
//    cout << str << endl;
//
//    auto start = high_resolution_clock::now();
//    double d = 0;
//    for (int i = 0; i < 1'000'000; ++i)
//    {
//        d += sqrt(sin(i) * cos(i));
//    }
//    auto end = high_resolution_clock::now();
//    auto diff = end - start;
//    cout << duration<double, milli>(diff).count() << "ms" << endl;
//}

void test_time_point()
{
    time_point<steady_clock> tp1;
    tp1 += 10min;
    auto d1 = tp1.time_since_epoch();
    duration<double> d2{d1};
    cout << d2.count() << " seconds" << endl;
    duration<double, nano> d3{d1};
    cout << d3.count() << " nanoseconds" << endl;
    time_point<steady_clock, seconds> tp_seconds{42s};
    time_point<steady_clock, milliseconds> tp_milli_seconds{tp_seconds};
    cout << tp_milli_seconds.time_since_epoch().count() << " ms" << endl;

    time_point<steady_clock, milliseconds> tp_milliseconds{42'424ms};
    auto tp_s = time_point_cast<seconds>(tp_milliseconds);
    cout << tp_s.time_since_epoch().count() << " ms" << endl;
}
//
//void test_date()
//{
//    year y1{2020};
//    auto y2 = 2020y;
//    month m1{6};
//    auto m2 = June;
//    day d1{22};
//    auto d2 = 22d;
//
//    year_month_day fulldate1{2020y, August, 12d};
//    auto fulldate2{2020y / August / 12d};
//    auto fulldate3{August / 12d / 2023y};
//    auto fulldate4{12d / August / 2023y};
//
//    year_month_day fulldate5{Monday[3] / June / 2023y};
//    auto june22{June / 22d};
//    auto june22_2020{2020y / june22};
//
//    auto last_day_of_ajune{June / last};
//    auto last_day_of_june2020{2020y / last_day_of_ajune};
//    auto last_monday_of_june2020{2020y / June / Monday[last]};
//
//    auto today = floor<days>(system_clock::now());
//    auto t1 = sys_days(2020y / June / 22d);
//    year_month_day ymd = floor<days>(t1);
//    year_month_day ymd1 = floor<days>(system_clock::now());
//
//    auto t2 = sys_days(2020y / June / 22d) + 9h + 35min + 10s;
//
//    auto t3{t2 + days(5)};
//    auto t4 = t3 + years(1);
//
//    cout << ymd << endl;
//}

//void  test_time_zone()
//{
//    const auto &database = get_tzdb();
//    for (const auto &item: database.zones)
//    {
//        cout << item.name() << "\n";
//    }
//
//    auto gmt = locate_zone("America/Bahia");
//    gmt->to_local(system_clock::now());
//}
}

namespace dt::exercise {

void test_22_1()
{
    duration<long> d1{42};
    duration<double, ratio<60>> d2{1.5};
    duration<double> d3{d1 + d2};
    auto d4 = duration_cast<duration<double, ratio<60>>>(d3);

    cout << d3.count() << " seconds" << endl;
    cout << d4.count() << " minutes" << endl;
}
//
//void test_22_2()
//{
//    std::regex r{R"(([0-9]{4})-(0?[1-9]|1[0-2])-(0?[1-9]|[1-2][0-9]|3[0-1]))"};
//    while (true)
//    {
//        string str;
//        if (!std::getline(cin, str) || str[0] == 'q')
//            break;
//        if (std::smatch m; std::regex_match(str, m, r))
//        {
//            int y, mon, d;
//            y = std::stoi(m[1].str());
//            mon = std::stoi(m[2].str());
//            d = std::stoi(m[3].str());
//            year_month_day ymd{year{y}, month{static_cast<unsigned int>(mon)}, day{static_cast<unsigned int>(d)}};
//            cout << ymd << "\n";
//        }
//    }
//}

void test_22_3()
{
    year_month_day ymd1{2020y / March / 31d};
    year_month_day ymd2{2023y / September / 25d};

    auto d1 = sys_days(ymd1);
    auto d2 = sys_days(ymd2);
    auto d = d2 - d1;
    cout << d.count() << " days" << endl;
}

//void test_22_4()
//{
//    year_month_day ymd{2020y / June / 22d};
//    year_month_weekday ymwd{ymd};
//    if (ymwd.ok())
//    {
//        cout << ymwd.weekday() << endl;
//    }
//    else
//        cout << "the day is invalid" << endl;
//}

//void test_22_5()
//{
////    2023-08-12 20:21:35 UTC
//    auto utc = sys_days{2023y / August / 12d} + 20h + 21min + 35s;
//    auto tokyo = locate_zone("Asia/Tokyo");
//    auto york = locate_zone("America/New_York");
//    auto gmt = locate_zone("GMT");
//    auto tokyo_t = tokyo->to_local(utc);
//    auto york_t = york->to_local(utc);
//    auto gmt_t = gmt->to_local(utc);
//    cout << "tokyo time: " << tokyo_t << endl;
//    cout << "new_york time: " << york_t << endl;
//    cout << "utc time: " << utc << endl;
//    cout << "gmt time: " << gmt_t << endl;
//
//    cout << "utc == gmt ? " << (utc.time_since_epoch() == gmt_t.time_since_epoch()) << endl;
//}

void test_22_6()
{
//    current tp
    auto cur_tp = system_clock::now();
    time_t cur_tt = system_clock::to_time_t(cur_tp);
    auto pt = localtime(&cur_tt);
    pt->tm_hour = 0;
    pt->tm_min = 0;
    pt->tm_sec = 0;
    time_t mid_t = mktime(pt);
    cout << cur_tt - mid_t << " seconds" << endl;

    duration<long> d{cur_tt - mid_t};
    hh_mm_ss<duration<long>> hms(d);
    cout << "hours: " << hms.hours()
         << " minutes: " << hms.minutes()
         << " seconds: " << hms.seconds()
         << endl;
}
}



int main()
{
    dt::test_ratio();
    dt::test_duration();
//    dt::test_clock();
//    dt::test_time_point();
//    dt::test_date();
//    dt::test_time_zone();
//    dt::exercise::test_22_1();
//    dt::exercise::test_22_2();
//    dt::exercise::test_22_3();
//    dt::exercise::test_22_4();
//    dt::exercise::test_22_5();
    dt::exercise::test_22_6();
    return 0;
}