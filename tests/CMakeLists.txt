include(GoogleTest)

file(COPY "${CMAKE_SOURCE_DIR}/data" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_executable(PreprocessorTest preprocessor_test.cpp)
gtest_discover_tests(PreprocessorTest)
target_link_libraries(PreprocessorTest PRIVATE GTest::gtest_main HPLC-LIB)


add_executable(LexerTest lexer_test.cpp)
gtest_discover_tests(LexerTest)
target_link_libraries(LexerTest PRIVATE GTest::gtest_main HPLC-LIB)