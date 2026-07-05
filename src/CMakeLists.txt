add_library(LIBRARY 
	preprocessor.cpp
)

file(COPY "${CMAKE_SOURCE_DIR}/data" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

target_include_directories(LIBRARY PUBLIC ${CMAKE_SOURCE_DIR}/include)
add_executable(High-Performance-Lang-Compiler main.cpp)
target_link_libraries(High-Performance-Lang-Compiler PRIVATE LIBRARY)
