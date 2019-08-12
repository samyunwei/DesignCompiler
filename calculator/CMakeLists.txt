set(proj_name "calculator")

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(lex_yacc)
include_directories(cpp)

BISON_TARGET(${proj_name}_parser ${CMAKE_SOURCE_DIR}/${proj_name}/lex_yacc/mycalc.y
        ${CMAKE_CURRENT_BINARY_DIR}/y.tab.c
        COMPILE_FLAGS --yacc
        )

FLEX_TARGET(${proj_name}_lexer ${CMAKE_SOURCE_DIR}/${proj_name}/lex_yacc/mycalc.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)


ADD_FLEX_BISON_DEPENDENCY(${proj_name}_lexer ${proj_name}_parser)

set(${proj_name}_src
        ${BISON_${proj_name}_parser_OUTPUTS}
        ${FLEX_${proj_name}_lexer_OUTPUTS}
        )

aux_source_directory(cpp cpp_src)

#set(lexer_src  cpp/lexicalanalyzer.c
#        cpp/token.h)
#
#set(parser_src cpp/token.h
#        cpp/parser.c
#        )

add_executable(my${proj_name} ${${proj_name}_src}
        )

#add_executable(lexer
#        ${lexer_src})

add_executable(my${proj_name}_cpp ${${proj_name}_src})

target_link_libraries(my${proj_name} m ${LEX_LIB})