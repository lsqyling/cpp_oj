find_package(fmt CONFIG REQUIRED)
add_executable(fmt_test fmt_test.cpp)
target_link_libraries(fmt_test PRIVATE fmt::fmt-header-only)


find_package(Eigen3 CONFIG REQUIRED)
add_executable(eigen3_test eigen3_test.cpp)
target_link_libraries(eigen3_test PRIVATE Eigen3::Eigen)


find_package(OpenCV REQUIRED)
add_executable(opencv_test opencv_test.cpp)
target_link_libraries(opencv_test PRIVATE ${OpenCV_LIBRARIES})

install(TARGETS fmt_test eigen3_test opencv_test
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION bin
)