//
// Created by zhang-kai on 6/6/25.
//

#pragma once
#include <memory>
#include <string>
#include <utility>
#include "ParserRuleContext.h"

class Position {
    /* This class is used for locating the position of the start and end of the node context
     * It is mainly used when errors occur
     */
private:
    size_t start_token_index = -1;
    antlr4::Token* start_token;
    size_t row;
    size_t col;
public:
    Position() = delete;
    Position(antlr4::ParserRuleContext *ctx) : start_token_index(ctx->getSourceInterval().a), start_token(ctx->getStart()), row(ctx->getStart()->getLine()), col(ctx->getStart()->getCharPositionInLine()) {
    }
    Position(antlr4::Token* token) : start_token(token), row(token->getLine()), col(token->getCharPositionInLine()) {}
    ~Position() = default;
    [[nodiscard]] std::size_t get_start_token_index() const {return start_token_index;}
    [[nodiscard]] std::string get_start_token() const {return start_token->getText();}
};




