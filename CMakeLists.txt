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
        src/include/frontend/ast/type/type_type.cpp
        src/include/frontend/ast/util/scope.cpp
        src/frontend/semantic_check.cpp
        src/frontend/global_scope_extractor.cpp
        src/frontend/ast_builder.cpp
        src/frontend/visit_control.cpp
        src/include/frontend/ast/stat_node/regular_stat_node/null_stat_node.h
)

target_link_libraries(Mx_Clion antlr4-runtime)