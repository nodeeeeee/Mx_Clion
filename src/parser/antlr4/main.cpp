//
// Created by zhang-kai on 6/1/25.
//
#include <iostream>
#include "antlr4-runtime.h"
#include "MxLexer.h"
#include "MxParser.h"
#include <filesystem>

using namespace antlr4;

int main(int argc, const char* argv[]) {
    // 读取文件（或者用 CinInputStream 读标准输入）
    std::ifstream stream;
    stream.open("testcases/codegen/t76");
    ANTLRInputStream input(stream);
    // 生成 Lexer
    MxLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    // 生成 Parser
    MxParser parser(&tokens);
    // 调用起始规则
    antlrcpp::Any result = parser.prog();
    // std::cout << "Any.toString() = " << result.toString() << std::endl;
    std::cout << "解析完成\n";
    return 0;
}
