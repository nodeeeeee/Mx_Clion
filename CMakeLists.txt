cmake_minimum_required(VERSION 3.31)
project(Mx_Clion)

set(CMAKE_CXX_STANDARD 20)

include_directories(/usr/include/antlr4-runtime)

add_executable(Mx_Clion src/parser/antlr4/main.cpp
        src/parser/antlr4/main.cpp
)

target_link_libraries(Mx_Clion antlr4-runtime)