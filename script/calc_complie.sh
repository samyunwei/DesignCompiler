#!/usr/bin/env bash
echo `pwd`
/usr/bin/yacc  -dv  ../calculator/lex_yacc/mycalc.y
/usr/bin/lex ../calculator/lex_yacc/mycalc.l
/usr/bin/gcc -o mycalc y.tab.c lex.yy.c