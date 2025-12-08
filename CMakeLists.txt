cmake_minimum_required(VERSION 3.31)
project(Mx_Clion)

set(CMAKE_CXX_STANDARD 20)

option(ENABLE_OJ_MODE "Enable running mode on the judger" OFF)

if(ENABLE_OJ_MODE)
    set(CMAKE_CXX_FLAGS "-Ofast -Dtestall")
    message(STATUS ">>> OJ_MODE is ON")
else()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -g -O0 ")
    message(STATUS ">>> OJ_MODE is OFF")
endif()
#address violation

include_directories(/usr/include/antlr4-runtime)
include_directories(src/include)
add_executable(Mx_Clion src/parser/antlr4/main.cpp
        src/parser/antlr4/MxListener.cpp
        src/parser/antlr4/MxParser.cpp
        src/parser/antlr4/MxBaseVisitor.cpp
        src/parser/antlr4/MxLexer.cpp
        src/include/frontend/ast/type/type_type.cpp
        src/include/util/scope.cpp
        src/frontend/semantic_check.cpp
        src/frontend/global_scope_extractor.cpp
        src/frontend/ast_builder.cpp
        src/frontend/visit_control.cpp
        src/include/frontend/ast/stat_node/regular_stat_node/null_stat_node.h
        src/include/frontend/ast/stat_node/regular_stat_node/expr_node/paren_expr_node.h
        src/include/frontend/ast/type/null_type.h
        src/include/frontend/ast/stat_node/regular_stat_node/block_stat_node.h
        src/include/backend/util/register.h
        src/include/backend/util/type/ir_type.h
        src/include/backend/util/type/ir_int_type.h
        src/include/backend/util/type/ir_bool_type.h
        src/include/backend/util/type/ir_string_type.h
        src/include/backend/util/type/ir_void_type.h
        src/include/backend/util/type/ir_type.cpp
        src/include/backend/stmt/global_stmt.h
        src/include/backend/util/block.h
        src/include/backend/util/constant.h
        src/include/backend/util/type/type_getter.h
        src/include/backend/util/ir_scope.h
        src/include/backend/stmt/stmt.h
        src/include/backend/util/ir_function.h
        src/include/backend/util/class_type.h
        src/include/backend/stmt/alloca_stmt.h
        src/include/backend/stmt/store_stmt.h
        src/include/backend/util/type/ir_ptr_type.h
        src/include/backend/stmt/load_stmt.h
        src/include/backend/stmt/call_stmt.h
        src/include/backend/stmt/binary_stmt.h
        src/include/backend/stmt/gep_stmt.h
        src/lib/builtin.c
        src/include/backend/stmt/icmp_stmt.h
        src/include/backend/stmt/variant_rep.h
        src/include/backend/stmt/br_stmt/br_conditional_stmt.h
        src/include/backend/stmt/br_stmt/br_unconditional_stmt.h
        #        src/include/backend/ir_generator.h
#        src/backend/ir_generator.cpp
)

target_link_libraries(Mx_Clion antlr4-runtime)