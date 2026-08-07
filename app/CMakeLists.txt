add_executable(HPLC main.cpp)
target_link_libraries(HPLC PRIVATE hplc-lib)
file(COPY "${CMAKE_SOURCE_DIR}/test/data" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")