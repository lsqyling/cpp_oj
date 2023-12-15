cmake_minimum_required(VERSION 3.15)

project(oj LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)


if (CMAKE_SYSTEM_NAME MATCHES Windows AND CMAKE_SYSTEM_VERSION MATCHES 10)
    message(STATUS "Windows 10 detected.")
    message(STATUS "Name: ${CMAKE_SYSTEM_NAME}")
    message(STATUS "Version: ${CMAKE_SYSTEM_VERSION}")
elseif (CMAKE_SYSTEM_NAME MATCHES Linux)
    message(STATUS "Linux detected.")
    message(STATUS "Name: ${CMAKE_SYSTEM_NAME}")
    message(STATUS "Version: ${CMAKE_SYSTEM_VERSION}")
else ()
    message(STATUS "Other OS!")
    message(STATUS "Name: ${CMAKE_SYSTEM_NAME}")
    message(STATUS "Version: ${CMAKE_SYSTEM_VERSION}")
endif ()


if (CMAKE_CXX_COMPILER_ID MATCHES Clang)
    message(STATUS "${CMAKE_CXX_COMPILER_ID}")
    add_compile_options(-stdlib=libc++)
elseif (CMAKE_CXX_COMPILER_ID MATCHES GNU)
    message(STATUS "${CMAKE_CXX_COMPILER_ID}")
    add_compile_options(-std=c++20)
endif ()

# pthread
find_package(Threads REQUIRED)
if (Threads_FOUND)
    message(STATUS "pthread finded!")
endif ()
# generate target
file(GLOB_RECURSE src_list
        LIST_DIRECTORIES false
        RELATIVE ${CMAKE_CURRENT_LIST_DIR}
        oj/*.cpp oj/*.c)

foreach (_v ${src_list})
    string(REGEX REPLACE / "_" _name ${_v})
    string(REPLACE .cpp "" _name ${_name})
    string(REPLACE .c "" _name ${_name})
    if (_name MATCHES primer0)
        add_executable(${_name} ${CMAKE_CURRENT_LIST_DIR}/${_v})
        target_link_libraries(${_name}
                PRIVATE
                Threads::Threads m)
    else ()
        add_executable(${_name} ${CMAKE_CURRENT_LIST_DIR}/${_v})
    endif ()
endforeach ()


add_subdirectory(professional_cpp)
add_subdirectory(cpp20_advanced_programing)
add_subdirectory(cpp_core_guide_lines)


