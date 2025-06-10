cmake_minimum_required(VERSION 3.31)
project(Mx_Clion)

set(CMAKE_CXX_STANDARD 20)

include_directories(/usr/include/antlr4-runtime)
include_directories(src/include)
add_executable(Mx_Clion src/parser/antlr4/main.cpp
        src/parser/antlr4/MxListener.cpp
        src/parser/antlr4/MxParser.cpp
        src/parser/antlr4/MxBaseVisitor.cpp
        src/include/frontend/ast/ast.h
        src/include/frontend/ast/ASTNode.h
        src/include/frontend/position.h
        src/include/frontend/ast/root_node.h
        src/include/frontend/ast/def_node/var_def_node.h
        src/include/frontend/ast/def_node/func_def_node.h
        src/include/frontend/ast/def_node/def_node.h
        src/include/frontend/ast/def_node/class_def_node.h
        src/include/frontend/ast/main_func_node.h
        src/include/frontend/ast/stat_node/regular_stat_node/expr_node/binary_expr_node.h
        src/include/frontend/ast/stat_node/regular_stat_node/expr_node/unary_expr_node.h
        src/include/frontend/ast/stat_node/regular_stat_node/expr_node/expr_node.h
        src/include/frontend/ast/stat_node/regular_stat_node/if_stat_node.h
        src/include/frontend/ast/stat_node/regular_stat_node/regular_stat_node.h
        src/include/frontend/ast/stat_node/stat_node.h
        src/include/frontend/ast/stat_node/regular_stat_node/expr_node/array_expr_node.h
        src/include/frontend/ast/terminal_node/terminal_node.h
        src/include/frontend/ast/terminal_node/literal_node.h
        #        src/frontend/ast_builder.cpp
)

target_link_libraries(Mx_Clion antlr4-runtime)