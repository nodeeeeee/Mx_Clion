cmake_minimum_required(VERSION 3.31)
project(Mx_Clion)

set(CMAKE_CXX_STANDARD 20)

include_directories(/usr/include/antlr4-runtime)
include_directories(src/include)
add_executable(Mx_Clion src/parser/antlr4/main.cpp
        src/parser/antlr4/MxListener.cpp
        src/parser/antlr4/MxParser.cpp
        src/parser/antlr4/MxBaseVisitor.cpp
        src/parser/antlr4/MxLexer.cpp
#        src/include/frontend/ast/stat_node/regular_stat_node/while_stat_node.h
#        src/include/frontend/ast/stat_node/regular_stat_node/return_stat_node.h
#        src/include/frontend/ast/stat_node/regular_stat_node/format_string_node.h
#        src/include/frontend/ast/stat_node/regular_stat_node/expr_node/func_call_node.h
#        src/include/frontend/ast/stat_node/regular_stat_node/expr_node/init_object_node.h
#        src/include/frontend/ast/terminal_node/id_node.h
#        src/include/frontend/ast/type/type_type.h
#        src/include/frontend/ast/type/bool_type.h
#        src/include/frontend/ast/type/int_type.h
#        src/include/frontend/ast/type/string_type.h
#        src/include/frontend/ast/type/void_type.h
#        src/include/frontend/ast/type/type_type.cpp
#        src/include/frontend/global_scope_extractor.h
#        src/include/frontend/ast/visit_control.h
#        src/include/frontend/ast/all_ast_nodes.h
#        src/include/frontend/scope.h
#        src/include/frontend/ast/stat_node/regular_stat_node/expr_node/ternary_expr_node.h
#        src/include/frontend/ast/util/scope.cpp
#        src/frontend/semantic_check.cpp
#        src/include/frontend/ast/semantic_check.h
#        src/frontend/global_scope_extractor.cpp
#        src/include/frontend/ast/util/function.h
#        src/include/frontend/ast/type/no_type.h
        #        src/include/frontend/ast/stat_node/regular_stat_node/for_stat_node.h
        #        src/include/frontend/ast/ast.h
#        src/include/frontend/ast/ASTNode.h
#        src/include/frontend/position.h
#        src/include/frontend/ast/root_node.h
#        src/include/frontend/ast/def_node/var_def_node.h
#        src/include/frontend/ast/def_node/func_def_node.h
#        src/include/frontend/ast/def_node/def_node.h
#        src/include/frontend/ast/def_node/class_def_node.h
#        src/include/frontend/ast/main_func_node.h
#        src/include/frontend/ast/stat_node/regular_stat_node/expr_node/binary_expr_node.h
#        src/include/frontend/ast/stat_node/regular_stat_node/expr_node/unary_expr_node.h
#        src/include/frontend/ast/stat_node/regular_stat_node/expr_node/expr_node.h
#        src/include/frontend/ast/stat_node/regular_stat_node/if_stat_node.h
#        src/include/frontend/ast/stat_node/regular_stat_node/regular_stat_node.h
#        src/include/frontend/ast/stat_node/stat_node.h
#        src/include/frontend/ast/stat_node/regular_stat_node/expr_node/array_expr_node.h
#        src/include/frontend/ast/terminal_node/terminal_node.h
#        src/include/frontend/ast/terminal_node/literal_node.h
#        src/include/frontend/ast/stat_node/regular_stat_node/expr_node/dot_expr_node.h
#        src/include/frontend/ast/stat_node/regular_stat_node/expr_node/init_array_expr_node.h
#        src/include/frontend/ast/stat_node/regular_stat_node/expr_node/index_expr_node.h
#        src/include/frontend/ast/stat_node/regular_stat_node/expr_node/null_expr_node.h
#        src/include/frontend/ast/def_node/class_func_def_node.h
#        src/include/frontend/ast/stat_node/regular_stat_node/assign_stat_node.h
#        src/include/frontend/ast/stat_node/regular_stat_node/block_node.h
        #        src/frontend/ast_builder.cpp
)

target_link_libraries(Mx_Clion antlr4-runtime)