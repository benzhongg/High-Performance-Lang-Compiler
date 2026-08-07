add_library(hplc-lib STATIC
    HPLC/lexer.cpp
    HPLC/macro_resolver.cpp
    HPLC/preprocessor.cpp
    HPLC/token.cpp    
)

target_include_directories(hplc-lib PUBLIC ${CMAKE_SOURCE_DIR}/include)