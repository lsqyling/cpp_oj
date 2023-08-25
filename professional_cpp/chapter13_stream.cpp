#include <iostream>
#include <fstream>
#include <filesystem>
#include "format.h"

namespace stream {
namespace fs = std::filesystem;
namespace ts = std::chrono;

int test_stream()
{
    std::ofstream fout{"stream.out"};
    if (!fout)
    {
        std::cerr << "Error opening stream.out for writing" << std::endl;
        return 1;
    }
//  1.  Output the string "54321".
    fout << "54321";
//  2. Verify that the marker is at position 5.
    std::streampos cur_pos{fout
    .tellp()};
    if (cur_pos == 5)
    {
        std::cout << "Test passed: Currently at position 5" << std::endl;
    }
    else
        std::cout << "Test failed: Not at position 5" << std::endl;
//    3. Move to position 2 in the output stream.
    fout.seekp(2, std::ios_base::beg);
//    4. Output a 0 in position 2 and close the output stream.
    fout << 0;
    fout.close();
//    5. Open an input stream on stream.out.
    std::ifstream fin{"stream.out"};
    if (!fin)
    {
        std::cerr << "Error opening stream.out for reading" << std::endl;
        return 1;
    }
//    6. Read the first token as an integer.
    int test_val;
    fin >> test_val;
    if (!fin)
    {
        std::cerr << "Error reading from file" << std::endl;
        return 1;
    }
//    7. Confirm that the value is 54021.
    const int expected = 54021;
    if (test_val == expected)
        std::cout << std::format("Test passed: Value is {}", expected) << std::endl;
    else
        std::cout << std::format("Test failed: Value is not {} (it was {})", expected, test_val) << std::endl;

    return 0;
}
void test_tie()
{
    std::ifstream ifs{"input.txt"};
    std::ofstream ofs{"input.txt"};

    ifs.tie(&ofs);
    ofs << "Hello there!";
    std::string next;
    ifs >> next;
    std::cout << next << std::endl;
}





void test_filesystem()
{
    fs::path p1{R"(D:\Foo\bar)"};
    fs::path p2{"D:/Foo/bar"};
    fs::path p3{"D:\\Foo\\bar\\MyFile.txt"};
    fs::path p4{R"(..\SomeFolder)"};
    fs::path p5{"/usr/lib/X11"};
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;

    fs::path p{"/usr/Foo"};
    p.append("Bar");
    p /= "Bar";
    std::cout << p << std::endl;

    for (const auto &item: p1)
    {
        std::cout << item  << "\n";
    }

    std::cout << p3.root_name() << "\n"
              << p3.filename() << "\n"
              << p3.stem() << "\n"
              << p3.extension() << "\n";

    fs::path p6{R"(D:\dev\workspace\clion\oj\professional_cpp\chapter13_stream.cpp)"};
    fs::directory_entry dir_entry{p6};
    std::cout << std::format("p6 exists: {}, \np6 regular_file: {},\np6 filesize: {}",
                             dir_entry.exists(), dir_entry.is_regular_file(),
                             dir_entry.file_size()) << std::endl;

    auto time_point{dir_entry.last_write_time()};
    time_t tt = ts::system_clock::to_time_t(ts::file_clock::to_sys(time_point));
    std::cout << std::put_time(std::localtime(&tt), "%b %d %Y %H:%M:%S") << std::endl;
};


void test_space()
{
    fs::space_info s{fs::space("D:\\")};
    std::cout << std::format("Capacity: {}\nFree: {}", s.capacity, s.free) << std::endl;
}

void print_parent_dir(const fs::path &p)
{
    if (!fs::exists(p))
        return;
    fs::recursive_directory_iterator begin{p};
    fs::recursive_directory_iterator end;

    for (auto it = begin; it != end; ++it)
    {
        const std::string spacer(it.depth() * 2, ' ');
        auto &entry = *it;
        if (fs::is_regular_file(entry))
        {
            std::cout << std::format("{} File: {} ({} bytes)", spacer, entry.path().string(),
                                     fs::file_size(entry)) << "\n";
        }
        else if (fs::is_directory(entry))
        {
            std::cout << std::format("{} Dir: {}", spacer, entry.path().string())
                      << "\n";
        }
    }
}

void print_parent_dir(const fs::path &p, size_t level)
{
    if (!fs::exists(p))
        return;
    const std::string spacer(level * 2, ' ');
    if (fs::is_regular_file(p))
    {
        std::cout << std::format("{}File: {} ({} bytes)", spacer, p.string(), fs::file_size(p))
                  << "\n";

    }
    else if (fs::is_directory(p))
    {
        std::cout << std::format("{}Dir: {}", spacer, p.string()) << "\n";
        for (auto &entry: fs::directory_iterator(p))
        {
            print_parent_dir(entry, level + 1);
        }
    }
}


void test_print_parent_dir()
{
    fs::path p{"d:/dev/workspace"};
    print_parent_dir(p);
    print_parent_dir(p, 0);
}
}




int  main(int argc, char *argv[])
{
    stream::test_stream();
    stream::test_tie();
    stream::test_filesystem();
    stream::test_space();
    stream::test_print_parent_dir();
    return 0;
}