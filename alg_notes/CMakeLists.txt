

file(GLOB src_list RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.cpp)
set(targets)
foreach (_v ${src_list})
    string(REPLACE .cpp "" _name ${_v})
    string(PREPEND _name "alg_notes_")

    if (${_name} MATCHES chapter OR ${_name} MATCHES _test)
        add_executable(${_name} ${_v})
        list(APPEND targets ${_name})
    endif ()
endforeach ()

install(TARGETS ${targets}
DESTINATION bin)

