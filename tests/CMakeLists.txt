add_executable(TEST test.cpp)
target_link_libraries(TEST PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(TEST)
