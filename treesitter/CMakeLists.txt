cmake_minimum_required(VERSION 3.28)

add_library(tree-sitter-hplcparser STATIC src/parser.c)
target_include_directories(tree-sitter-hplcparser PUBLIC src)
set_target_properties(tree-sitter-hplcparser PROPERTIES C_STANDARD 11)

find_program(TREE_SITTER_CLI tree-sitter)
if(TREE_SITTER_CLI)
    add_custom_target(hplc-tree-sitter-test
        COMMAND ${TREE_SITTER_CLI} test
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endif()