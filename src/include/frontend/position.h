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
    std::size_t start_token_index;

    antlr4::Token* start_token;
public:
    Position() = delete;
    Position(antlr4::ParserRuleContext *ctx) : start_token_index(ctx->getSourceInterval().a), start_token(ctx->getStart()) {

    }
    ~Position() = default;
    [[nodiscard]] std::size_t get_start_token_index() const {return start_token_index;}
    [[nodiscard]] std::string get_start_token() const {return start_token->getText();}
};




