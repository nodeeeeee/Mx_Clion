#pragma once
#include "BaseErrorListener.h"
using namespace antlr4;

class MxErrorListener : public antlr4::BaseErrorListener
{
    void syntaxError(Recognizer* recognizer, Token* offendingSymbol, size_t line, size_t charPositionInLine,
                     const std::string& msg, std::exception_ptr e) override
    {
        /* Whenever there is a syntax error, the function will be called, and exit with return value 1.
         *
         */
        exit(1);
    }
};
