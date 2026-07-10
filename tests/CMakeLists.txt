include(GoogleTest)

file(COPY "${CMAKE_SOURCE_DIR}/data" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_executable(PreprocessorTest preprocessor_test.cpp)
gtest_discover_tests(PreprocessorTest DISCOVERY_TIMEOUT 60)
target_link_libraries(PreprocessorTest PRIVATE GTest::gtest_main HPLC-LIB)


add_executable(LexerTest lexer_test.cpp)
gtest_discover_tests(LexerTest DISCOVERY_TIMEOUT 60)
target_link_libraries(LexerTest PRIVATE GTest::gtest_main HPLC-LIB)

add_executable(FileReaderTest fileReader_test.cpp)
gtest_discover_tests(FileReaderTest DISCOVERY_TIMEOUT 60)
target_link_libraries(FileReaderTest PRIVATE GTest::gtest_main HPLC-LIB)