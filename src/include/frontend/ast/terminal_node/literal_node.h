//
// Created by zhang-kai on 6/10/25.
//

#pragma once
#include "terminal_node.h"

class LiteralNode : public TerminalNode {
private:
    std::string literal_type;
    bool is_null;
    std::optional<std::string> string_value;
    std::optional<size_t> int_value;
    std::optional<bool> bool_value;
public:
    LiteralNode() = delete;
    explicit LiteralNode(antlr4::Token* token) : TerminalNode("literal", Position(token)) {
        if (token->getType() == MxParser::INTEGER) {
            literal_type = "int";
            int_value = std::stoi(token->getText());
        } else if (token->getType() == MxParser::BOOL) {
            literal_type = "bool";
            bool_value = token->getText() == "true" ? true : false;
        } else if (token->getType() == MxParser::STRING) {
            literal_type = "string";
            string_value = token->getText();
        } else if (token->getType() == MxParser::NULL_) {
            is_null = true;
        }
    }
};
