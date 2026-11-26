add_executable(test_proga test.cpp)
target_link_libraries(test_proga PRIVATE geometry Boost::program_options)
add_test(NAME proga_tests COMMAND test_proga)