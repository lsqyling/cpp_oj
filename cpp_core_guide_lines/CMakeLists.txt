# generate target
file(GLOB_RECURSE src_list
        LIST_DIRECTORIES false
        RELATIVE ${CMAKE_CURRENT_LIST_DIR}
        *.cpp *.h)

set(target_src_list)
foreach (_v ${src_list})
    if (NOT _v MATCHES _test.cpp AND NOT _v MATCHES chapter AND NOT _v MATCHES include)
        list(APPEND target_src_list ${CMAKE_CURRENT_LIST_DIR}/${_v})
    endif ()
endforeach ()


set(target_name)

foreach (_v ${src_list})
    if (_v MATCHES _test.cpp)
        string(REPLACE .cpp "" _name ${_v})
        list(APPEND target_name ${_name})
        add_executable(${_name} ${CMAKE_CURRENT_LIST_DIR}/${_v} ${target_src_list})
    endif ()
    if (_v MATCHES chapter)
        string(REPLACE .cpp "" _name ${_v})
        list(APPEND target_name ${_name})
        add_executable(${_name} ${CMAKE_CURRENT_LIST_DIR}/${_v} ${target_src_list})
        if (_v MATCHES multi_thread)
            target_link_directories(${_name}
                    PRIVATE
                    Threads::Threads)
        endif ()
    endif ()
endforeach ()

install(TARGETS ${target_name}
ARCHIVE DESTINATION lib
RUNTIME DESTINATION bin
LIBRARY DESTINATION bin)

#install(FILES chapter5_class.h
#DESTINATION include
#)

install(FILES README.md
DESTINATION doc
)
unset(target_src_list)
unset(target_name)
