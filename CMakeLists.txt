cmake_minimum_required(VERSION 3.28) 
project(High-Performance-Lang-Compiler
		LANGUAGES
		CXX
)

enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
	set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
	set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

add_library(openmp INTERFACE)
find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
	target_link_libraries(openmp INTERFACE OpenMP::OpenMP_CXX)
endif()

include(FetchContent)

FetchContent_Declare(
	tree_sitter
	GIT_REPOSITORY https://github.com/tree-sitter/tree-sitter.git
	GIT_TAG v0.22.6
	SOURCE_SUBDIR lib
)
FetchContent_MakeAvailable(tree_sitter)

FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
	googlebenchmark
	GIT_REPOSITORY https://github.com/google/benchmark.git
	GIT_TAG v1.9.4
)
FetchContent_MakeAvailable(googlebenchmark)

add_subdirectory(src)
add_subdirectory(treesitter)
add_subdirectory(test)
add_subdirectory(app)