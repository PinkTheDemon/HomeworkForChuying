include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(logger_test logger_test.cpp)

target_link_libraries(logger_test
    minilog
    gtest
    gtest_main
)
