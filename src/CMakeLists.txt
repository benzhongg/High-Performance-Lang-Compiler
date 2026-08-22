add_library(hplc-lib STATIC
    HPLC/ast_builder.cpp
    HPLC/macro_resolver.cpp
    HPLC/preprocessor.cpp
    HPLC/parser.cpp
)

target_include_directories(hplc-lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(hplc-lib PUBLIC tree-sitter-hplcparser tree-sitter)