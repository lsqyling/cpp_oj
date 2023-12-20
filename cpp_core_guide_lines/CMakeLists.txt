# generate target
file(GLOB src_list RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.cpp)

set(target_list)


foreach (_v ${src_list})
    if (_v MATCHES _test.cpp)
        string(REPLACE .cpp "" _name ${_v})
        string(PREPEND _name "cpp_core_guide_lines_")

        list(APPEND target_list ${_name})
        add_executable(${_name} ${_v})
    endif ()
endforeach ()

install(TARGETS ${target_list}
ARCHIVE DESTINATION lib
RUNTIME DESTINATION bin
LIBRARY DESTINATION bin)

unset(target_list)