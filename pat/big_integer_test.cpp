#include <fstream>
#include <random>
#include <iostream>

#include "big_integer.h"
//4M
constexpr int N = 4 * (1 << 20);
const std::string src_data = "../pat/big_number.data";
const std::string data_sum = "../pat/big_number_sum.data";
const std::string data_multi = "../pat/big_number_multi.data";
const std::string data_multi_by_long = "../pat/big_number_multi_bylong.data";

void generate_bignum_datafile(long many)
{
    std::ofstream fout(src_data, std::ofstream::out);
    static std::default_random_engine e;
    static std::uniform_int_distribution<uint64_t > u(0x3fff'ffff'ffff'ffffL,
                                                      0x7fff'ffff'ffff'ffffL);
    for (int i = 0; i < many; ++i)
    {
        fout << u(e) << " " << u(e) << "\n";
    }
}

void generate_bignum_sum_multi_datafile()
{
    std::ifstream fin(src_data, std::ifstream::in);
    std::ofstream fout(data_sum, std::ofstream::out);
    std::ofstream fos(data_multi, std::ofstream::out);
    bigi::big_integer n1, n2;
    while (fin >> n1 >> n2)
    {
        fout << n1 << " " << n2 << " " << (n1 + n2) << "\n";
        fos << n1 << " " << n2 << " " << (n1 * n2) << "\n";
    }
}


void generate_bignum_multi_bylong_datafile()
{
    std::ifstream fin(src_data, std::ifstream::in);
    std::ofstream fout(data_multi_by_long, std::ofstream::out);
    bigi::big_integer n1;
    long n2;
    while (fin >> n1 >> n2)
    {
        fout << n1 << " " << n2 << " " << (n1 * n2) << "\n";
    }
}

bool judge_same(const std::string &path1, const std::string &path2)
{
    std::ifstream if1(path1, std::ifstream::in);
    std::ifstream if2(path2, std::ifstream::in);
    std::string line1, line2;
    while (1)
    {

        std::getline(if1, line1);
        std::getline(if2, line2);
        if (if1.eof() && if2.eof())
            break;
        if (line1 != line2)
        {
            std::cout << line1 << std::endl;
            std::cout << line2 << std::endl;
            return false;
        }
    }
    return true;
}

void test_bignum_file()
{
    generate_bignum_datafile(N);
    generate_bignum_sum_multi_datafile();
    generate_bignum_multi_bylong_datafile();

    if (judge_same(data_multi, data_multi_by_long))
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;
}

void test_remove_front_zero()
{
    std::string s = "0000abcdefj0";
    std::string s1 = "0c0101010";
    std::string s2 = "abc00000";
    std::string s3 = "0";
    std::string s4 = "0000";
    bigi::remove_front_zero(s);
    bigi::remove_front_zero(s1);
    bigi::remove_front_zero(s2);
    bigi::remove_front_zero(s3);
    bigi::remove_front_zero(s4);
    std::cout << s << "\n"
              << s1 << "\n"
              << s2 << "\n"
              << s3 << "\n"
              << s4 << "\n";
}




int main(int argc, char **argv)
{

    bigi::big_integer n1 = 0, n2 = 10;
    std::string sn1 = "5218296995529832183", sn2 = "7068641233167674308";
    std::cout << bigi::value_of(sn1, 10) << "\n" << bigi::value_of(sn2, 10) << "\n";
    std::cout << n1 << "\n" << n2 << "\n";
    std::cout << (n1 * n2) << "\n";
    test_bignum_file();

    test_remove_front_zero();

    return 0;

}


