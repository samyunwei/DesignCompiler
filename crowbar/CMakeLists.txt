set(proj_name "crowbar")

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(lex_yacc)
include_directories(cpp)
include_directories(include)

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

aux_source_directory(include include_src)

add_executable(my${proj_name} ${${proj_name}_src}
        ${include_src}
        )

add_executable(my${proj_name}_cpp ${${proj_name}_src}
        ${include_src}
        ${cpp_src}
        )

target_link_libraries(my${proj_name} ${LEX_LIB})