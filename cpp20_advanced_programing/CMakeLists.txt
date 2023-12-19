
# generate target
file(GLOB_RECURSE src_list
        LIST_DIRECTORIES false
        RELATIVE ${CMAKE_CURRENT_LIST_DIR}
        *.cpp *.h)

set(target_src_list)
foreach (_v ${src_list})
    if (NOT _v MATCHES _test.cpp AND NOT _v MATCHES part AND NOT _v MATCHES include)
        list(APPEND target_src_list ${CMAKE_CURRENT_LIST_DIR}/${_v})
    endif ()
endforeach ()

#find_package(co_context REQUIRED)


foreach (_v ${src_list})
    if (_v MATCHES _test.cpp)
        string(REPLACE .cpp "" _name ${_v})
        add_executable(${_name} ${CMAKE_CURRENT_LIST_DIR}/${_v} ${target_src_list})
    endif ()
    if (_v MATCHES _coroutine)
#        string(REPLACE .cpp "" _name ${_v})
#        add_executable(${_name} ${CMAKE_CURRENT_LIST_DIR}/${_v} ${target_src_list})
#        target_link_libraries(${_name}
#                PRIVATE
#                co_context)
#        if (_v MATCHES multi_thread)
#            target_link_directories(${_name}
#                    PRIVATE
#                    Threads::Threads)
#        endif ()
    elseif (_v MATCHES part)
        string(REPLACE .cpp "" _name ${_v})
        add_executable(${_name} ${CMAKE_CURRENT_LIST_DIR}/${_v} ${target_src_list})
        if (_v MATCHES multi_thread)
            target_link_directories(${_name}
                    PRIVATE
                    Threads::Threads)
        endif ()
    endif ()


endforeach ()

unset(target_src_list)




