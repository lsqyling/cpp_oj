# generate target
file(GLOB_RECURSE src_list
        LIST_DIRECTORIES false
        RELATIVE ${CMAKE_CURRENT_LIST_DIR}
        pat/*.cpp pat/*.c)

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
