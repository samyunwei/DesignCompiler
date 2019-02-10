find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
find_library(LEX_LIB REQUIRED)

set(CMAKE_AUTOMOC ON)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(lex_yacc)
include_directories(cpp)

BISON_TARGET(calc_parser ${CMAKE_SOURCE_DIR}/calculator/lex_yacc/mycalc.y
        ${CMAKE_CURRENT_BINARY_DIR}/y.tab.c
        COMPILE_FLAGS --yacc
        )

FLEX_TARGET(calc_lexer ${CMAKE_SOURCE_DIR}/calculator/lex_yacc/mycalc.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)


ADD_FLEX_BISON_DEPENDENCY(calc_lexer calc_parser)

set (calc_src
        ${BISON_calc_parser_OUTPUTS}
        ${FLEX_calc_lexer_OUTPUTS}
        )

aux_source_directory(cpp cpp_src)

add_executable(mycalc ${calc_src}
        )

add_executable(mycalc_cpp
        ${cpp_src})

target_link_libraries(mycalc ${LEX_LIB})