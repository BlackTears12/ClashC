cmake_minimum_required(VERSION 3.16)

project(ClashC LANGUAGES C)

add_executable(ClashC
    main.c
    lib/str.h
    lib/str.c
    lib/vector.h
    lang/ast_expr.h
    lang/function.h
    lang/ast_stment.h
    lang/ast.h
    parse/lexer.h
    parse/lexer.c
    parse/token.h
    parse/token.c
    lib/diagnostics.h
    lib/diagnostics.c
    parse/parser.h
    lang/function.c
    parse/parser.c
    lang/symbol.h
    lang/symbol.c
    lang/ast_expr.c
    lib/vector.c
    lang/ast_stment.c
    lib/alloc.h
)

include(GNUInstallDirs)

include_directories(lib lang parse)

install(TARGETS ClashC
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
