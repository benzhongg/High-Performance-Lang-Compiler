include(GoogleTest)

file(COPY "${CMAKE_SOURCE_DIR}/test/data" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_executable(PreprocessorTest preprocessor_test.cpp)
target_link_libraries(PreprocessorTest PRIVATE GTest::gtest_main)
target_link_libraries(PreprocessorTest PRIVATE hplc-lib)
gtest_discover_tests(PreprocessorTest DISCOVERY_TIMEOUT 60)

add_executable(ASTBuilderTest ast_builder_test.cpp)
target_link_libraries(ASTBuilderTest PRIVATE GTest::gtest_main hplc-lib)
gtest_discover_tests(ASTBuilderTest DISCOVERY_TIMEOUT 60)


add_executable(FileReaderTest fileReader_test.cpp)
gtest_discover_tests(FileReaderTest DISCOVERY_TIMEOUT 60)
target_link_libraries(FileReaderTest PRIVATE GTest::gtest_main hplc-lib)