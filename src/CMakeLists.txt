add_library(HPLC-LIB INTERFACE)
file(COPY "${CMAKE_SOURCE_DIR}/data" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
target_include_directories(HPLC-LIB INTERFACE ${CMAKE_SOURCE_DIR}/include)


add_executable(High-Performance-Lang-Compiler main.cpp)
target_link_libraries(High-Performance-Lang-Compiler PRIVATE GTest::gtest_main HPLC-LIB)