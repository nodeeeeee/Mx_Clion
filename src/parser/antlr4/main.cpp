//
// Created by zhang-kai on 6/1/25.
//

/*The whole thing is very confusing.
 *Firstly, we should use ANTLRInputStream input(std::cin); to make an interface for sema/test_all.sh
 *Secondly, the working directory when you key in the test_all.mx command is in the shell working directory
 *
 */
#include <iostream>
#include "antlr4-runtime.h"
#include "parser/MxLexer.h"
#include "parser/MxParser.h"
#include "frontend/MxErrorListener.h"
#include <filesystem>
#include <thread>      // std::this_thread::sleep_for
#include <chrono>      // std::chrono::milliseconds

using namespace antlr4;
namespace fs = std::filesystem;

static std::vector<fs::directory_entry> loadEntries(const std::string& listFile)
{
    std::vector<fs::directory_entry> ret;
    std::ifstream in(listFile);
    std::string line;
    while (std::getline(in, line))
    {
        // 跳过空行
        if (line.empty()) continue;
        fs::path p(line);
        // 可选：只加入扩展名为 .mx 的路径
        if (p.extension() != ".mx") continue;
        ret.emplace_back(p);
    }
    return ret;
}


int main(int argc, const char* argv[])
{
    // 读取文件（或者用 CinInputStream 读标准输入）
    // const std::string listFilename ="testcases/sema/judgelist.txt";
    // auto entries = loadEntries(listFilename);
    // freopen("output.txt", "a", stdout);
    // for (const auto& entry : fs::directory_iterator("testcases/sema/basic-package"))
    // for (const auto& entry : entries)
    // {
        // if (entry.path().filename().extension() != ".mx")
        // {
            // continue;
        // }
        std::ifstream stream;

        stream.open("testcases/sema/symbol-package/symbol-2.mx");
        // stream.open(entry.path());
        // std::cout << entry.path() << std::endl;


        // stream.open("testcases/sema/" + entry.path().string());
        // std::filesystem::path cwd = std::filesystem::current_path();
        // std::cout << "当前工作目录: " << cwd << std::endl;

        // if (stream.is_open())
        // {
            // std::cout << "open file: " << entry.path() << std::endl;
        // }
        // else
        // {
            // std::cout << "open file failed" << std::endl;
        // }



        // std::string stream;
        // std::cin >> stream;


        // ANTLRInputStream input(stream);
        MxErrorListener error_listener;
        ANTLRInputStream input(std::cin);
        // 生成 Lexer
        MxLexer lexer(&input);
        lexer.addErrorListener(&error_listener);
        CommonTokenStream tokens(&lexer);
        tokens.fill();
        for (auto token : tokens.getTokens()) {
            std::cout << token->toString() << std::endl;
        }
        // 生成 Parser

        MxParser parser(&tokens);
        // parser.setErrorHandler(std::make_shared<BailErrorStrategy>());  This is a built-in function to catch errors in parser.
        parser.addErrorListener(&error_listener);
        // 调用起始规则

            tree::ParseTree* tree = parser.prog();

            // std::cout << stream << std::endl;
            std::cout << tree->toStringTree(&parser) << std::endl << std::endl;
            std::cout << "解析完成\n";
        // }

        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
    return 0;
}